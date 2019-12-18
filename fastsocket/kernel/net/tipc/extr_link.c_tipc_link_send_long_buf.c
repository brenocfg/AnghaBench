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
typedef  int /*<<< orphan*/  unchar ;
typedef  scalar_t__ u32 ;
struct tipc_msg {int dummy; } ;
struct sk_buff {int /*<<< orphan*/ * data; } ;
struct TYPE_2__ {int /*<<< orphan*/  sent_fragments; int /*<<< orphan*/  sent_fragmented; } ;
struct link {scalar_t__ addr; TYPE_1__ stats; int /*<<< orphan*/  long_msg_seq_no; } ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  FIRST_FRAGMENT ; 
 int /*<<< orphan*/  FRAGMENT ; 
 scalar_t__ INT_H_SIZE ; 
 int /*<<< orphan*/  LAST_FRAGMENT ; 
 int /*<<< orphan*/  MSG_FRAGMENTER ; 
 struct sk_buff* buf_acquire (scalar_t__) ; 
 int /*<<< orphan*/  buf_discard (struct sk_buff*) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 scalar_t__ link_max_pkt (struct link*) ; 
 int /*<<< orphan*/  mod (int /*<<< orphan*/ ) ; 
 scalar_t__ msg_data_sz (struct tipc_msg*) ; 
 scalar_t__ msg_destnode (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_init (struct tipc_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  msg_link_selector (struct tipc_msg*) ; 
 scalar_t__ msg_routed (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_set_fragm_no (struct tipc_msg*,scalar_t__) ; 
 int /*<<< orphan*/  msg_set_link_selector (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_long_msgno (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_prevnode (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_size (struct tipc_msg*,scalar_t__) ; 
 int /*<<< orphan*/  msg_set_type (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 scalar_t__ msg_short (struct tipc_msg*) ; 
 scalar_t__ msg_size (struct tipc_msg*) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,struct tipc_msg*,scalar_t__) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data_offset (struct sk_buff*,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  tipc_link_is_up (struct link*) ; 
 int /*<<< orphan*/  tipc_link_send_buf (struct link*,struct sk_buff*) ; 
 int /*<<< orphan*/  tipc_own_addr ; 
 int /*<<< orphan*/  warn (char*) ; 

int tipc_link_send_long_buf(struct link *l_ptr, struct sk_buff *buf)
{
	struct tipc_msg *inmsg = buf_msg(buf);
	struct tipc_msg fragm_hdr;
	u32 insize = msg_size(inmsg);
	u32 dsz = msg_data_sz(inmsg);
	unchar *crs = buf->data;
	u32 rest = insize;
	u32 pack_sz = link_max_pkt(l_ptr);
	u32 fragm_sz = pack_sz - INT_H_SIZE;
	u32 fragm_no = 1;
	u32 destaddr;

	if (msg_short(inmsg))
		destaddr = l_ptr->addr;
	else
		destaddr = msg_destnode(inmsg);

	if (msg_routed(inmsg))
		msg_set_prevnode(inmsg, tipc_own_addr);

	/* Prepare reusable fragment header: */

	msg_init(&fragm_hdr, MSG_FRAGMENTER, FIRST_FRAGMENT,
		 INT_H_SIZE, destaddr);
	msg_set_link_selector(&fragm_hdr, msg_link_selector(inmsg));
	msg_set_long_msgno(&fragm_hdr, mod(l_ptr->long_msg_seq_no++));
	msg_set_fragm_no(&fragm_hdr, fragm_no);
	l_ptr->stats.sent_fragmented++;

	/* Chop up message: */

	while (rest > 0) {
		struct sk_buff *fragm;

		if (rest <= fragm_sz) {
			fragm_sz = rest;
			msg_set_type(&fragm_hdr, LAST_FRAGMENT);
		}
		fragm = buf_acquire(fragm_sz + INT_H_SIZE);
		if (fragm == NULL) {
			warn("Link unable to fragment message\n");
			dsz = -ENOMEM;
			goto exit;
		}
		msg_set_size(&fragm_hdr, fragm_sz + INT_H_SIZE);
		skb_copy_to_linear_data(fragm, &fragm_hdr, INT_H_SIZE);
		skb_copy_to_linear_data_offset(fragm, INT_H_SIZE, crs,
					       fragm_sz);
		/*  Send queued messages first, if any: */

		l_ptr->stats.sent_fragments++;
		tipc_link_send_buf(l_ptr, fragm);
		if (!tipc_link_is_up(l_ptr))
			return dsz;
		msg_set_fragm_no(&fragm_hdr, ++fragm_no);
		rest -= fragm_sz;
		crs += fragm_sz;
		msg_set_type(&fragm_hdr, FRAGMENT);
	}
exit:
	buf_discard(buf);
	return dsz;
}