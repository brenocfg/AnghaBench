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
 scalar_t__ BVME_SCC_A_ADDR ; 
 scalar_t__ M147_SCC_A_ADDR ; 
 scalar_t__ MACH_IS_BVME6000 ; 
 scalar_t__ MACH_IS_MVME147 ; 
 scalar_t__ MACH_IS_MVME16x ; 
 scalar_t__ MVME_SCC_A_ADDR ; 
 int /*<<< orphan*/  scc_delay () ; 

__attribute__((used)) static void scc_ch_write (char ch)
{
	volatile char *p = NULL;
	
#ifdef CONFIG_MVME147_SCC
	if (MACH_IS_MVME147)
		p = (volatile char *)M147_SCC_A_ADDR;
#endif
#ifdef CONFIG_MVME162_SCC
	if (MACH_IS_MVME16x)
		p = (volatile char *)MVME_SCC_A_ADDR;
#endif
#ifdef CONFIG_BVME6000_SCC
	if (MACH_IS_BVME6000)
		p = (volatile char *)BVME_SCC_A_ADDR;
#endif

	do {
		scc_delay();
	}
	while (!(*p & 4));
	scc_delay();
	*p = 8;
	scc_delay();
	*p = ch;
}