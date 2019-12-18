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
 int /*<<< orphan*/  FLAC__format_get_max_rice_partition_order_from_blocksize (unsigned int) ; 
 int FLAC__format_get_max_rice_partition_order_from_blocksize_limited_max_and_predictor_order (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

unsigned FLAC__format_get_max_rice_partition_order(unsigned blocksize, unsigned predictor_order)
{
	return
		FLAC__format_get_max_rice_partition_order_from_blocksize_limited_max_and_predictor_order(
			FLAC__format_get_max_rice_partition_order_from_blocksize(blocksize),
			blocksize,
			predictor_order
		);
}