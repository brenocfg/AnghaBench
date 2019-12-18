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
struct sk_buff {int dummy; } ;
struct cardstate {int dummy; } ;
struct bc_state {int /*<<< orphan*/  corrupted; scalar_t__ ignore; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  gigaset_isdn_rcv_err (struct bc_state*) ; 

__attribute__((used)) static inline void gigaset_rcv_error(struct sk_buff *procskb,
				     struct cardstate *cs,
				     struct bc_state *bcs)
{
	if (procskb)
		dev_kfree_skb(procskb);

	if (bcs->ignore)
		--bcs->ignore;
	else {
		++bcs->corrupted;
		gigaset_isdn_rcv_err(bcs);
	}
}