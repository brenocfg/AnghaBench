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
struct perf_top {scalar_t__ guest_us_samples; scalar_t__ guest_kernel_samples; scalar_t__ exact_samples; scalar_t__ kernel_samples; scalar_t__ us_samples; scalar_t__ samples; } ;

/* Variables and functions */

void perf_top__reset_sample_counters(struct perf_top *top)
{
	top->samples = top->us_samples = top->kernel_samples =
	top->exact_samples = top->guest_kernel_samples =
	top->guest_us_samples = 0;
}