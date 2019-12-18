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
 int* local_port_range ; 
 int /*<<< orphan*/  local_port_range_lock ; 
 unsigned int read_seqbegin (int /*<<< orphan*/ *) ; 
 scalar_t__ read_seqretry (int /*<<< orphan*/ *,unsigned int) ; 

void phonet_get_local_port_range(int *min, int *max)
{
	unsigned seq;
	do {
		seq = read_seqbegin(&local_port_range_lock);
		if (min)
			*min = local_port_range[0];
		if (max)
			*max = local_port_range[1];
	} while (read_seqretry(&local_port_range_lock, seq));
}