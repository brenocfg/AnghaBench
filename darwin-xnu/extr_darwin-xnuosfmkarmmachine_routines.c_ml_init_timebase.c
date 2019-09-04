#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* vm_offset_t ;
typedef  TYPE_1__* tbd_ops_t ;
typedef  int /*<<< orphan*/  cpu_data_t ;
struct TYPE_4__ {void* tbd_fiq_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  BootCpuData ; 
 void* rtclock_timebase_addr ; 
 TYPE_1__ rtclock_timebase_func ; 
 void* rtclock_timebase_val ; 

void ml_init_timebase(
	void		*args,
	tbd_ops_t	tbd_funcs,
	vm_offset_t	int_address,
	vm_offset_t	int_value)
{
	cpu_data_t     *cpu_data_ptr;

	cpu_data_ptr = (cpu_data_t *)args;

	if ((cpu_data_ptr == &BootCpuData)
	    && (rtclock_timebase_func.tbd_fiq_handler == (void *)NULL)) {
		rtclock_timebase_func = *tbd_funcs;
		rtclock_timebase_addr = int_address;
		rtclock_timebase_val = int_value;
	}
}