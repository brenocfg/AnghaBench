#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* mach_timebase_info_t ;
struct TYPE_6__ {scalar_t__ numer; scalar_t__ denom; } ;
typedef  TYPE_2__ mach_timebase_info_data_t ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_5__ {scalar_t__ numer; scalar_t__ denom; } ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ mach_timebase_info_trap (TYPE_2__*) ; 

kern_return_t
mach_timebase_info(mach_timebase_info_t info){
    static mach_timebase_info_data_t cached_info;

	/*
	 * This is racy, but because it is safe to initialize twice we avoid a
	 * barrier in the fast path by risking double initialization.
	 */
    if (cached_info.numer == 0 || cached_info.denom == 0){
        kern_return_t kr = mach_timebase_info_trap(&cached_info);
        if (kr != KERN_SUCCESS) return kr;
    }

	info->numer = cached_info.numer;
	info->denom = cached_info.denom;

    return KERN_SUCCESS;
}