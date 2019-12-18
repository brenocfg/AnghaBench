#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int data; } ;

/* Variables and functions */
 int CPLB_VALID ; 
 int MAX_CPLBS ; 
 int first_switched_icplb ; 
 int* icplb_rr_index ; 
 TYPE_1__** icplb_tbl ; 

__attribute__((used)) static int evict_one_icplb(unsigned int cpu)
{
	int i;
	for (i = first_switched_icplb; i < MAX_CPLBS; i++)
		if ((icplb_tbl[cpu][i].data & CPLB_VALID) == 0)
			return i;
	i = first_switched_icplb + icplb_rr_index[cpu];
	if (i >= MAX_CPLBS) {
		i -= MAX_CPLBS - first_switched_icplb;
		icplb_rr_index[cpu] -= MAX_CPLBS - first_switched_icplb;
	}
	icplb_rr_index[cpu]++;
	return i;
}