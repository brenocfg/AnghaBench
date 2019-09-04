#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {uintptr_t arg1; uintptr_t arg2; uintptr_t arg3; uintptr_t arg4; scalar_t__ arg5; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  debugid; } ;

/* Variables and functions */
 size_t KD_EARLY_BUFFER_NBUFS ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int /*<<< orphan*/ ,uintptr_t,uintptr_t,uintptr_t,uintptr_t,int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_number () ; 
 TYPE_1__* kd_early_buffer ; 
 scalar_t__ kd_early_done ; 
 size_t kd_early_index ; 
 int kd_early_overflow ; 
 int /*<<< orphan*/  mach_absolute_time () ; 
 scalar_t__ master_cpu ; 

void
kernel_debug_early(
	uint32_t	debugid,
	uintptr_t	arg1,
	uintptr_t	arg2,
	uintptr_t	arg3,
	uintptr_t	arg4)
{
	/* If early tracing is over, use the normal path. */
	if (kd_early_done) {
		KERNEL_DEBUG_CONSTANT(debugid, arg1, arg2, arg3, arg4, 0);
		return;
	}

	/* Do nothing if the buffer is full or we're not on the boot cpu. */
	kd_early_overflow = kd_early_index >= KD_EARLY_BUFFER_NBUFS;
	if (kd_early_overflow || cpu_number() != master_cpu) {
		return;
	}

	kd_early_buffer[kd_early_index].debugid = debugid;
	kd_early_buffer[kd_early_index].timestamp = mach_absolute_time();
	kd_early_buffer[kd_early_index].arg1 = arg1;
	kd_early_buffer[kd_early_index].arg2 = arg2;
	kd_early_buffer[kd_early_index].arg3 = arg3;
	kd_early_buffer[kd_early_index].arg4 = arg4;
	kd_early_buffer[kd_early_index].arg5 = 0;
	kd_early_index++;
}