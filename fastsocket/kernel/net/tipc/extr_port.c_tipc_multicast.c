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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_name_seq {int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; int /*<<< orphan*/  type; } ;
struct tipc_msg {int dummy; } ;
struct sk_buff {int dummy; } ;
struct port_list {scalar_t__ count; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {struct tipc_msg phdr; } ;
struct port {int /*<<< orphan*/  user_port; TYPE_1__ publ; } ;
struct iovec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MAX_MSG_SIZE ; 
 int /*<<< orphan*/  MCAST_H_SIZE ; 
 int /*<<< orphan*/  TIPC_MCAST_MSG ; 
 int /*<<< orphan*/  TIPC_NODE_SCOPE ; 
 int /*<<< orphan*/  buf_discard (struct sk_buff*) ; 
 int msg_build (struct tipc_msg*,struct iovec const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct sk_buff**) ; 
 int /*<<< orphan*/  msg_set_hdr_sz (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_namelower (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_nametype (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_nameupper (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_type (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_copy (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int tipc_bclink_send_msg (struct sk_buff*) ; 
 int tipc_nametbl_mc_translate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct port_list*) ; 
 struct port* tipc_port_deref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_port_list_free (struct port_list*) ; 
 int /*<<< orphan*/  tipc_port_recv_mcast (struct sk_buff*,struct port_list*) ; 
 scalar_t__ unlikely (int) ; 

int tipc_multicast(u32 ref, struct tipc_name_seq const *seq, u32 domain,
		   u32 num_sect, struct iovec const *msg_sect)
{
	struct tipc_msg *hdr;
	struct sk_buff *buf;
	struct sk_buff *ibuf = NULL;
	struct port_list dports = {0, NULL, };
	struct port *oport = tipc_port_deref(ref);
	int ext_targets;
	int res;

	if (unlikely(!oport))
		return -EINVAL;

	/* Create multicast message */

	hdr = &oport->publ.phdr;
	msg_set_type(hdr, TIPC_MCAST_MSG);
	msg_set_nametype(hdr, seq->type);
	msg_set_namelower(hdr, seq->lower);
	msg_set_nameupper(hdr, seq->upper);
	msg_set_hdr_sz(hdr, MCAST_H_SIZE);
	res = msg_build(hdr, msg_sect, num_sect, MAX_MSG_SIZE,
			!oport->user_port, &buf);
	if (unlikely(!buf))
		return res;

	/* Figure out where to send multicast message */

	ext_targets = tipc_nametbl_mc_translate(seq->type, seq->lower, seq->upper,
						TIPC_NODE_SCOPE, &dports);

	/* Send message to destinations (duplicate it only if necessary) */

	if (ext_targets) {
		if (dports.count != 0) {
			ibuf = skb_copy(buf, GFP_ATOMIC);
			if (ibuf == NULL) {
				tipc_port_list_free(&dports);
				buf_discard(buf);
				return -ENOMEM;
			}
		}
		res = tipc_bclink_send_msg(buf);
		if ((res < 0) && (dports.count != 0)) {
			buf_discard(ibuf);
		}
	} else {
		ibuf = buf;
	}

	if (res >= 0) {
		if (ibuf)
			tipc_port_recv_mcast(ibuf, &dports);
	} else {
		tipc_port_list_free(&dports);
	}
	return res;
}