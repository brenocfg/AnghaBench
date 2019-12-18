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

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  cpu_mid_prop () ; 
 int prom_getintdefault (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sparc_cpu_model ; 
 scalar_t__ sun4m ; 

__attribute__((used)) static int check_cpu_node(int nd, int *cur_inst,
			  int (*compare)(int, int, void *), void *compare_arg,
			  int *prom_node, int *mid)
{
	if (!compare(nd, *cur_inst, compare_arg)) {
		if (prom_node)
			*prom_node = nd;
		if (mid) {
			*mid = prom_getintdefault(nd, cpu_mid_prop(), 0);
			if (sparc_cpu_model == sun4m)
				*mid &= 3;
		}
		return 0;
	}

	(*cur_inst)++;

	return -ENODEV;
}