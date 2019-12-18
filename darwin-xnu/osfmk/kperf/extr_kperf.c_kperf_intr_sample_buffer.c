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
struct kperf_sample {int dummy; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  assert (int) ; 
 unsigned int cpu_number () ; 
 unsigned int intr_samplec ; 
 struct kperf_sample* intr_samplev ; 
 scalar_t__ ml_get_interrupts_enabled () ; 

struct kperf_sample *
kperf_intr_sample_buffer(void)
{
	unsigned ncpu = cpu_number();

	assert(ml_get_interrupts_enabled() == FALSE);
	assert(ncpu < intr_samplec);

	return &(intr_samplev[ncpu]);
}