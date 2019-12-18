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
typedef  int /*<<< orphan*/  u32 ;
struct tcf_result {int dummy; } ;
struct tcf_proto {int prio; int /*<<< orphan*/  protocol; } ;
struct sk_buff {int /*<<< orphan*/  tc_verd; int /*<<< orphan*/  protocol; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  G_TC_VERD (int /*<<< orphan*/ ) ; 
 scalar_t__ MAX_REC_LOOP ; 
 int /*<<< orphan*/  SET_TC_VERD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TC_ACT_RECLASSIFY ; 
 int TC_ACT_SHOT ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int,int /*<<< orphan*/ ) ; 
 int tc_classify_compat (struct sk_buff*,struct tcf_proto*,struct tcf_result*) ; 

int tc_classify(struct sk_buff *skb, struct tcf_proto *tp,
		struct tcf_result *res)
{
	int err = 0;
	__be16 protocol;
#ifdef CONFIG_NET_CLS_ACT
	struct tcf_proto *otp = tp;
reclassify:
#endif
	protocol = skb->protocol;

	err = tc_classify_compat(skb, tp, res);
#ifdef CONFIG_NET_CLS_ACT
	if (err == TC_ACT_RECLASSIFY) {
		u32 verd = G_TC_VERD(skb->tc_verd);
		tp = otp;

		if (verd++ >= MAX_REC_LOOP) {
			printk("rule prio %u protocol %02x reclassify loop, "
			       "packet dropped\n",
			       tp->prio&0xffff, ntohs(tp->protocol));
			return TC_ACT_SHOT;
		}
		skb->tc_verd = SET_TC_VERD(skb->tc_verd, verd);
		goto reclassify;
	}
#endif
	return err;
}