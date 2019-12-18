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
struct TYPE_2__ {scalar_t__ num_bytes; } ;

/* Variables and functions */
 TYPE_1__* sp_banks ; 

unsigned long probe_memory(void)
{
	unsigned long total = 0;
	int i;

	for (i = 0; sp_banks[i].num_bytes; i++)
		total += sp_banks[i].num_bytes;

	return total;
}