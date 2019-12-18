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
struct tc_cbq_lssopt {int /*<<< orphan*/  change; int /*<<< orphan*/  offtime; scalar_t__ minidle; int /*<<< orphan*/  maxidle; int /*<<< orphan*/  avpkt; int /*<<< orphan*/  level; int /*<<< orphan*/  ewma_log; int /*<<< orphan*/  flags; } ;
struct sk_buff {int len; } ;
struct cbq_class {int /*<<< orphan*/  offtime; scalar_t__ minidle; int /*<<< orphan*/  maxidle; int /*<<< orphan*/  avpkt; int /*<<< orphan*/  level; int /*<<< orphan*/  ewma_log; int /*<<< orphan*/ * share; int /*<<< orphan*/ * borrow; } ;
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 int /*<<< orphan*/  NLA_PUT (struct sk_buff*,int /*<<< orphan*/ ,int,struct tc_cbq_lssopt*) ; 
 int /*<<< orphan*/  TCA_CBQ_LSSOPT ; 
 int /*<<< orphan*/  TCF_CBQ_LSS_BOUNDED ; 
 int /*<<< orphan*/  TCF_CBQ_LSS_ISOLATED ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 

__attribute__((used)) static __inline__ int cbq_dump_lss(struct sk_buff *skb, struct cbq_class *cl)
{
	unsigned char *b = skb_tail_pointer(skb);
	struct tc_cbq_lssopt opt;

	opt.flags = 0;
	if (cl->borrow == NULL)
		opt.flags |= TCF_CBQ_LSS_BOUNDED;
	if (cl->share == NULL)
		opt.flags |= TCF_CBQ_LSS_ISOLATED;
	opt.ewma_log = cl->ewma_log;
	opt.level = cl->level;
	opt.avpkt = cl->avpkt;
	opt.maxidle = cl->maxidle;
	opt.minidle = (u32)(-cl->minidle);
	opt.offtime = cl->offtime;
	opt.change = ~0;
	NLA_PUT(skb, TCA_CBQ_LSSOPT, sizeof(opt), &opt);
	return skb->len;

nla_put_failure:
	nlmsg_trim(skb, b);
	return -1;
}