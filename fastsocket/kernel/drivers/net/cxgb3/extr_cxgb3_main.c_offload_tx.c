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
struct t3cdev {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int t3_offload_tx (struct t3cdev*,struct sk_buff*) ; 

__attribute__((used)) static inline int offload_tx(struct t3cdev *tdev, struct sk_buff *skb)
{
	int ret;

	local_bh_disable();
	ret = t3_offload_tx(tdev, skb);
	local_bh_enable();
	return ret;
}