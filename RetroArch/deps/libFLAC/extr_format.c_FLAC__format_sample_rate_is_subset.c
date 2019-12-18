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
 int /*<<< orphan*/  FLAC__format_sample_rate_is_valid (unsigned int) ; 

FLAC__bool FLAC__format_sample_rate_is_subset(unsigned sample_rate)
{
	if(
		!FLAC__format_sample_rate_is_valid(sample_rate) ||
		(
			sample_rate >= (1u << 16) &&
			!(sample_rate % 1000 == 0 || sample_rate % 10 == 0)
		)
	) {
		return false;
	}
	else
		return true;
}