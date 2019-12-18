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
 scalar_t__ kVMPressureNormal ; 
 scalar_t__ memorystatus_vm_pressure_level ; 

int
memorystatus_get_pressure_status_kdp() {
	return (kVMPressureNormal != memorystatus_vm_pressure_level) ? 1 : 0;
}