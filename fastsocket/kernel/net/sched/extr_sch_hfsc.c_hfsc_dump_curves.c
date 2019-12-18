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
struct sk_buff {int len; } ;
struct hfsc_class {int cl_flags; int /*<<< orphan*/  cl_usc; int /*<<< orphan*/  cl_fsc; int /*<<< orphan*/  cl_rsc; } ;

/* Variables and functions */
 int HFSC_FSC ; 
 int HFSC_RSC ; 
 int HFSC_USC ; 
 int /*<<< orphan*/  TCA_HFSC_FSC ; 
 int /*<<< orphan*/  TCA_HFSC_RSC ; 
 int /*<<< orphan*/  TCA_HFSC_USC ; 
 scalar_t__ hfsc_dump_sc (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
hfsc_dump_curves(struct sk_buff *skb, struct hfsc_class *cl)
{
	if ((cl->cl_flags & HFSC_RSC) &&
	    (hfsc_dump_sc(skb, TCA_HFSC_RSC, &cl->cl_rsc) < 0))
		goto nla_put_failure;

	if ((cl->cl_flags & HFSC_FSC) &&
	    (hfsc_dump_sc(skb, TCA_HFSC_FSC, &cl->cl_fsc) < 0))
		goto nla_put_failure;

	if ((cl->cl_flags & HFSC_USC) &&
	    (hfsc_dump_sc(skb, TCA_HFSC_USC, &cl->cl_usc) < 0))
		goto nla_put_failure;

	return skb->len;

 nla_put_failure:
	return -1;
}