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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int kperf_sampling_disable () ; 
 int kperf_sampling_enable () ; 

__attribute__((used)) static int
kperf_sampling_set(uint32_t sample_start)
{
	if (sample_start) {
		return kperf_sampling_enable();
	} else {
		return kperf_sampling_disable();
	}
}