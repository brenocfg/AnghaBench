#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct tipc_msg {int dummy; } ;
struct sk_buff {struct sk_buff* next; } ;

/* Variables and functions */
 scalar_t__ FIRST_FRAGMENT ; 
 scalar_t__ LONG_H_SIZE ; 
 scalar_t__ MCAST_H_SIZE ; 
 scalar_t__ TIPC_MAX_USER_MSG_SIZE ; 
 scalar_t__ TIPC_MCAST_MSG ; 
 struct sk_buff* buf_acquire (scalar_t__) ; 
 int /*<<< orphan*/  buf_discard (struct sk_buff*) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  dbg (char*,...) ; 
 int /*<<< orphan*/  dbg_print_buf_chain (struct sk_buff*) ; 
 scalar_t__ get_expected_frags (struct sk_buff*) ; 
 scalar_t__ get_fragm_size (struct sk_buff*) ; 
 scalar_t__ msg_data (struct tipc_msg*) ; 
 scalar_t__ msg_data_sz (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_dbg (struct tipc_msg*,char*) ; 
 int msg_fragm_no (struct tipc_msg*) ; 
 scalar_t__ msg_long_msgno (struct tipc_msg*) ; 
 scalar_t__ msg_orignode (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_reset_reroute_cnt (struct tipc_msg*) ; 
 scalar_t__ msg_seqno (struct tipc_msg*) ; 
 scalar_t__ msg_size (struct tipc_msg*) ; 
 scalar_t__ msg_type (struct tipc_msg*) ; 
 int /*<<< orphan*/  set_expected_frags (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  set_fragm_size (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  set_long_msg_seqno (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,struct tipc_msg*,scalar_t__) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data_offset (struct sk_buff*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  warn (char*) ; 

int tipc_link_recv_fragment(struct sk_buff **pending, struct sk_buff **fb,
			    struct tipc_msg **m)
{
	struct sk_buff *prev = NULL;
	struct sk_buff *fbuf = *fb;
	struct tipc_msg *fragm = buf_msg(fbuf);
	struct sk_buff *pbuf = *pending;
	u32 long_msg_seq_no = msg_long_msgno(fragm);

	*fb = NULL;
	msg_dbg(fragm,"FRG<REC<");

	/* Is there an incomplete message waiting for this fragment? */

	while (pbuf && ((msg_seqno(buf_msg(pbuf)) != long_msg_seq_no)
			|| (msg_orignode(fragm) != msg_orignode(buf_msg(pbuf))))) {
		prev = pbuf;
		pbuf = pbuf->next;
	}

	if (!pbuf && (msg_type(fragm) == FIRST_FRAGMENT)) {
		struct tipc_msg *imsg = (struct tipc_msg *)msg_data(fragm);
		u32 msg_sz = msg_size(imsg);
		u32 fragm_sz = msg_data_sz(fragm);
		u32 exp_fragm_cnt = msg_sz/fragm_sz + !!(msg_sz % fragm_sz);
		u32 max =  TIPC_MAX_USER_MSG_SIZE + LONG_H_SIZE;
		if (msg_type(imsg) == TIPC_MCAST_MSG)
			max = TIPC_MAX_USER_MSG_SIZE + MCAST_H_SIZE;
		if (msg_size(imsg) > max) {
			msg_dbg(fragm,"<REC<Oversized: ");
			buf_discard(fbuf);
			return 0;
		}
		pbuf = buf_acquire(msg_size(imsg));
		if (pbuf != NULL) {
			pbuf->next = *pending;
			*pending = pbuf;
			skb_copy_to_linear_data(pbuf, imsg,
						msg_data_sz(fragm));
			/*  Prepare buffer for subsequent fragments. */

			set_long_msg_seqno(pbuf, long_msg_seq_no);
			set_fragm_size(pbuf,fragm_sz);
			set_expected_frags(pbuf,exp_fragm_cnt - 1);
		} else {
			warn("Link unable to reassemble fragmented message\n");
		}
		buf_discard(fbuf);
		return 0;
	} else if (pbuf && (msg_type(fragm) != FIRST_FRAGMENT)) {
		u32 dsz = msg_data_sz(fragm);
		u32 fsz = get_fragm_size(pbuf);
		u32 crs = ((msg_fragm_no(fragm) - 1) * fsz);
		u32 exp_frags = get_expected_frags(pbuf) - 1;
		skb_copy_to_linear_data_offset(pbuf, crs,
					       msg_data(fragm), dsz);
		buf_discard(fbuf);

		/* Is message complete? */

		if (exp_frags == 0) {
			if (prev)
				prev->next = pbuf->next;
			else
				*pending = pbuf->next;
			msg_reset_reroute_cnt(buf_msg(pbuf));
			*fb = pbuf;
			*m = buf_msg(pbuf);
			return 1;
		}
		set_expected_frags(pbuf,exp_frags);
		return 0;
	}
	dbg(" Discarding orphan fragment %x\n",fbuf);
	msg_dbg(fragm,"ORPHAN:");
	dbg("Pending long buffers:\n");
	dbg_print_buf_chain(*pending);
	buf_discard(fbuf);
	return 0;
}