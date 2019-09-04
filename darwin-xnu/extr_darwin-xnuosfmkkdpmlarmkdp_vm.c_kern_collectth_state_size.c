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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct thread_command {int dummy; } ;
typedef  int /*<<< orphan*/  arm_state_hdr_t ;

/* Variables and functions */
 int ARM_THREAD_STATE32_COUNT ; 
 int ml_get_max_cpu_number () ; 

void
kern_collectth_state_size(uint64_t * tstate_count, uint64_t * tstate_size)
{
    uint64_t    count = ml_get_max_cpu_number() + 1;

    *tstate_count = count;
    *tstate_size  = sizeof(struct thread_command)
	          + (sizeof(arm_state_hdr_t) 
#if defined(__arm64__)
	          + ARM_THREAD_STATE64_COUNT * sizeof(uint32_t));
#else
	          + ARM_THREAD_STATE32_COUNT * sizeof(uint32_t));
#endif
}