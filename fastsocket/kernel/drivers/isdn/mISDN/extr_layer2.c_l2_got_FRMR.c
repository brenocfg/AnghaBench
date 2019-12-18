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
struct sk_buff {int* data; } ;
struct layer2 {int /*<<< orphan*/  flag; } ;
struct FsmInst {scalar_t__ state; struct layer2* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_L3_INIT ; 
 scalar_t__ IsUA (int*) ; 
 int /*<<< orphan*/  MDL_ERROR_IND ; 
 scalar_t__ ST_L2_7 ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  establishlink (struct FsmInst*) ; 
 scalar_t__ l2addrsize (struct layer2*) ; 
 int /*<<< orphan*/  l2mgr (struct layer2*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
l2_got_FRMR(struct FsmInst *fi, int event, void *arg)
{
	struct layer2 *l2 = fi->userdata;
	struct sk_buff *skb = arg;

	skb_pull(skb, l2addrsize(l2) + 1);

	if (!(skb->data[0] & 1) || ((skb->data[0] & 3) == 1) || /* I or S */
	    (IsUA(skb->data) && (fi->state == ST_L2_7))) {
		l2mgr(l2, MDL_ERROR_IND, (void *) 'K');
		establishlink(fi);
		test_and_clear_bit(FLG_L3_INIT, &l2->flag);
	}
	dev_kfree_skb(skb);
}