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
struct niu_parent {scalar_t__* ldg_map; } ;
struct niu_ldg {scalar_t__ ldg_num; } ;
struct niu {struct niu_parent* parent; } ;

/* Variables and functions */
 int LDN_MAX ; 
 int niu_ldn_irq_enable (struct niu*,int,int) ; 

__attribute__((used)) static int niu_enable_ldn_in_ldg(struct niu *np, struct niu_ldg *lp, int on)
{
	struct niu_parent *parent = np->parent;
	int i;

	for (i = 0; i <= LDN_MAX; i++) {
		int err;

		if (parent->ldg_map[i] != lp->ldg_num)
			continue;

		err = niu_ldn_irq_enable(np, i, on);
		if (err)
			return err;
	}
	return 0;
}