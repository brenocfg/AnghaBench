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
typedef  int FLAC__bool ;

/* Variables and functions */

FLAC__bool FLAC__format_blocksize_is_subset(unsigned blocksize, unsigned sample_rate)
{
	if(blocksize > 16384)
		return false;
	else if(sample_rate <= 48000 && blocksize > 4608)
		return false;
	else
		return true;
}