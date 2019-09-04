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
typedef  int /*<<< orphan*/  mach_port_name_t ;

/* Variables and functions */
 int /*<<< orphan*/  __TSD_MACH_THREAD_SELF ; 
 scalar_t__ _os_tsd_get_direct (int /*<<< orphan*/ ) ; 

__attribute__((used)) __inline static mach_port_name_t
_os_get_self(void)
{
	mach_port_name_t self = (mach_port_name_t)(uintptr_t)(void *)_os_tsd_get_direct(__TSD_MACH_THREAD_SELF);
	return self;
}