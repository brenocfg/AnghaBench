#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int denom; int numer; } ;
typedef  TYPE_2__ mach_timebase_info_data_t ;
struct TYPE_5__ {int frequency; } ;
struct TYPE_7__ {TYPE_1__ ns_time; } ;

/* Variables and functions */
 TYPE_4__ _glfw ; 
 int /*<<< orphan*/  mach_timebase_info (TYPE_2__*) ; 

void _glfwInitTimerNS(void)
{
    mach_timebase_info_data_t info;
    mach_timebase_info(&info);

    _glfw.ns_time.frequency = (info.denom * 1e9) / info.numer;
}