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
 scalar_t__ MACH_IS_BVME6000 ; 
 scalar_t__ MACH_IS_MVME147 ; 
 scalar_t__ MACH_IS_MVME16x ; 
 int bvme6000_scc_init () ; 
 int mvme147_scc_init () ; 
 int mvme162_scc_init () ; 

__attribute__((used)) static int vme_scc_init(void)
{
	int res = -ENODEV;

#ifdef CONFIG_MVME147_SCC
	if (MACH_IS_MVME147)
		res = mvme147_scc_init();
#endif
#ifdef CONFIG_MVME162_SCC
	if (MACH_IS_MVME16x)
		res = mvme162_scc_init();
#endif
#ifdef CONFIG_BVME6000_SCC
	if (MACH_IS_BVME6000)
		res = bvme6000_scc_init();
#endif
	return res;
}