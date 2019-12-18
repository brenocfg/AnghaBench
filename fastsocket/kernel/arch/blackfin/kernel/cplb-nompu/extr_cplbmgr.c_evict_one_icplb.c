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
 int MAX_CPLBS ; 
 int first_switched_icplb ; 
 int* icplb_rr_index ; 

__attribute__((used)) static int evict_one_icplb(int cpu)
{
	int i = first_switched_icplb + icplb_rr_index[cpu];
	if (i >= MAX_CPLBS) {
		i -= MAX_CPLBS - first_switched_icplb;
		icplb_rr_index[cpu] -= MAX_CPLBS - first_switched_icplb;
	}
	icplb_rr_index[cpu]++;
	return i;
}