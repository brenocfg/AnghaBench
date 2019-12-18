#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct tipc_msg {int dummy; } ;
struct sk_buff {int dummy; } ;
struct link {scalar_t__ exp_msg_count; int /*<<< orphan*/  reset_checkpoint; int /*<<< orphan*/  name; int /*<<< orphan*/  next_in_no; TYPE_2__* b_ptr; TYPE_1__* owner; } ;
struct TYPE_4__ {int /*<<< orphan*/  net_plane; } ;
struct TYPE_3__ {struct link** links; } ;

/* Variables and functions */
 scalar_t__ DUPLICATE_MSG ; 
 int /*<<< orphan*/  INT_H_SIZE ; 
 scalar_t__ START_CHANGEOVER ; 
 int /*<<< orphan*/  buf_discard (struct sk_buff*) ; 
 struct sk_buff* buf_extract (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  dbg (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  dbg_print_link (struct link*,char*) ; 
 int /*<<< orphan*/  err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ less (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod (int /*<<< orphan*/ ) ; 
 size_t msg_bearer_id (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_dbg (struct tipc_msg*,char*) ; 
 struct tipc_msg* msg_get_wrapped (struct tipc_msg*) ; 
 scalar_t__ msg_msgcnt (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_seqno (struct tipc_msg*) ; 
 scalar_t__ msg_type (struct tipc_msg*) ; 
 scalar_t__ tipc_link_is_up (struct link*) ; 
 int /*<<< orphan*/  tipc_link_reset (struct link*) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int link_recv_changeover_msg(struct link **l_ptr,
				    struct sk_buff **buf)
{
	struct sk_buff *tunnel_buf = *buf;
	struct link *dest_link;
	struct tipc_msg *msg;
	struct tipc_msg *tunnel_msg = buf_msg(tunnel_buf);
	u32 msg_typ = msg_type(tunnel_msg);
	u32 msg_count = msg_msgcnt(tunnel_msg);

	dest_link = (*l_ptr)->owner->links[msg_bearer_id(tunnel_msg)];
	if (!dest_link) {
		msg_dbg(tunnel_msg, "NOLINK/<REC<");
		goto exit;
	}
	if (dest_link == *l_ptr) {
		err("Unexpected changeover message on link <%s>\n",
		    (*l_ptr)->name);
		goto exit;
	}
	dbg("%c<-%c:", dest_link->b_ptr->net_plane,
	    (*l_ptr)->b_ptr->net_plane);
	*l_ptr = dest_link;
	msg = msg_get_wrapped(tunnel_msg);

	if (msg_typ == DUPLICATE_MSG) {
		if (less(msg_seqno(msg), mod(dest_link->next_in_no))) {
			msg_dbg(tunnel_msg, "DROP/<REC<");
			goto exit;
		}
		*buf = buf_extract(tunnel_buf,INT_H_SIZE);
		if (*buf == NULL) {
			warn("Link changeover error, duplicate msg dropped\n");
			goto exit;
		}
		msg_dbg(tunnel_msg, "TNL<REC<");
		buf_discard(tunnel_buf);
		return 1;
	}

	/* First original message ?: */

	if (tipc_link_is_up(dest_link)) {
		msg_dbg(tunnel_msg, "UP/FIRST/<REC<");
		info("Resetting link <%s>, changeover initiated by peer\n",
		     dest_link->name);
		tipc_link_reset(dest_link);
		dest_link->exp_msg_count = msg_count;
		dbg("Expecting %u tunnelled messages\n", msg_count);
		if (!msg_count)
			goto exit;
	} else if (dest_link->exp_msg_count == START_CHANGEOVER) {
		msg_dbg(tunnel_msg, "BLK/FIRST/<REC<");
		dest_link->exp_msg_count = msg_count;
		dbg("Expecting %u tunnelled messages\n", msg_count);
		if (!msg_count)
			goto exit;
	}

	/* Receive original message */

	if (dest_link->exp_msg_count == 0) {
		warn("Link switchover error, "
		     "got too many tunnelled messages\n");
		msg_dbg(tunnel_msg, "OVERDUE/DROP/<REC<");
		dbg_print_link(dest_link, "LINK:");
		goto exit;
	}
	dest_link->exp_msg_count--;
	if (less(msg_seqno(msg), dest_link->reset_checkpoint)) {
		msg_dbg(tunnel_msg, "DROP/DUPL/<REC<");
		goto exit;
	} else {
		*buf = buf_extract(tunnel_buf, INT_H_SIZE);
		if (*buf != NULL) {
			msg_dbg(tunnel_msg, "TNL<REC<");
			buf_discard(tunnel_buf);
			return 1;
		} else {
			warn("Link changeover error, original msg dropped\n");
		}
	}
exit:
	*buf = NULL;
	buf_discard(tunnel_buf);
	return 0;
}