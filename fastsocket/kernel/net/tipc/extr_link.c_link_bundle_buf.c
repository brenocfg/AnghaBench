#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct tipc_msg {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  sent_bundled; } ;
struct link {TYPE_1__ stats; } ;

/* Variables and functions */
 scalar_t__ MSG_BUNDLER ; 
 scalar_t__ OPEN_MSG ; 
 scalar_t__ align (scalar_t__) ; 
 int /*<<< orphan*/  buf_discard (struct sk_buff*) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  dbg (char*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ link_max_pkt (struct link*) ; 
 int /*<<< orphan*/  msg_dbg (struct tipc_msg*,char*) ; 
 scalar_t__ msg_msgcnt (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_seqno (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_set_msgcnt (struct tipc_msg*,scalar_t__) ; 
 int /*<<< orphan*/  msg_set_size (struct tipc_msg*,scalar_t__) ; 
 scalar_t__ msg_size (struct tipc_msg*) ; 
 scalar_t__ msg_type (struct tipc_msg*) ; 
 scalar_t__ msg_user (struct tipc_msg*) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data_offset (struct sk_buff*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 scalar_t__ skb_tailroom (struct sk_buff*) ; 

__attribute__((used)) static int link_bundle_buf(struct link *l_ptr,
			   struct sk_buff *bundler,
			   struct sk_buff *buf)
{
	struct tipc_msg *bundler_msg = buf_msg(bundler);
	struct tipc_msg *msg = buf_msg(buf);
	u32 size = msg_size(msg);
	u32 bundle_size = msg_size(bundler_msg);
	u32 to_pos = align(bundle_size);
	u32 pad = to_pos - bundle_size;

	if (msg_user(bundler_msg) != MSG_BUNDLER)
		return 0;
	if (msg_type(bundler_msg) != OPEN_MSG)
		return 0;
	if (skb_tailroom(bundler) < (pad + size))
		return 0;
	if (link_max_pkt(l_ptr) < (to_pos + size))
		return 0;

	skb_put(bundler, pad + size);
	skb_copy_to_linear_data_offset(bundler, to_pos, buf->data, size);
	msg_set_size(bundler_msg, to_pos + size);
	msg_set_msgcnt(bundler_msg, msg_msgcnt(bundler_msg) + 1);
	dbg("Packed msg # %u(%u octets) into pos %u in buf(#%u)\n",
	    msg_msgcnt(bundler_msg), size, to_pos, msg_seqno(bundler_msg));
	msg_dbg(msg, "PACKD:");
	buf_discard(buf);
	l_ptr->stats.sent_bundled++;
	return 1;
}