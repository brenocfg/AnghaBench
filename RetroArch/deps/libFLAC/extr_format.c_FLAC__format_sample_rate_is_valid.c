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
 unsigned int FLAC__MAX_SAMPLE_RATE ; 

FLAC__bool FLAC__format_sample_rate_is_valid(unsigned sample_rate)
{
	if(sample_rate == 0 || sample_rate > FLAC__MAX_SAMPLE_RATE) {
		return false;
	}
	else
		return true;
}