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

/* Variables and functions */
 int CPU_PA_RISC1_1 ; 
 int EINVAL ; 
 int INT_MAX ; 
#define  _SC_CPU_VERSION 129 
#define  _SC_OPEN_MAX 128 

int hpux_sysconf(int which)
{
	switch (which) {
	case _SC_CPU_VERSION:
		return CPU_PA_RISC1_1;
	case _SC_OPEN_MAX:
		return INT_MAX;
	default:
		return -EINVAL;
	}
}