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
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {scalar_t__ cpu_base_timebase; } ;

/* Variables and functions */
 TYPE_1__* getCpuDatap () ; 
 scalar_t__ ml_get_hwclock () ; 

uint64_t
ml_get_timebase()
{
	return (ml_get_hwclock() + getCpuDatap()->cpu_base_timebase);
}