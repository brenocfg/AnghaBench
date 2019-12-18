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
 int /*<<< orphan*/  FLAC__MAX_RICE_PARTITION_ORDER ; 
 int MIN (int /*<<< orphan*/ ,unsigned int) ; 

unsigned FLAC__format_get_max_rice_partition_order_from_blocksize(unsigned blocksize)
{
	unsigned max_rice_partition_order = 0;
	while(!(blocksize & 1)) {
		max_rice_partition_order++;
		blocksize >>= 1;
	}
	return MIN(FLAC__MAX_RICE_PARTITION_ORDER, max_rice_partition_order);
}