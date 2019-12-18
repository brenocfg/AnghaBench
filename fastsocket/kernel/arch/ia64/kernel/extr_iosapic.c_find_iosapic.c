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
struct TYPE_2__ {unsigned int gsi_base; unsigned int num_rte; } ;

/* Variables and functions */
 int NR_IOSAPICS ; 
 TYPE_1__* iosapic_lists ; 

__attribute__((used)) static inline int
find_iosapic (unsigned int gsi)
{
	int i;

	for (i = 0; i < NR_IOSAPICS; i++) {
		if ((unsigned) (gsi - iosapic_lists[i].gsi_base) <
		    iosapic_lists[i].num_rte)
			return i;
	}

	return -1;
}