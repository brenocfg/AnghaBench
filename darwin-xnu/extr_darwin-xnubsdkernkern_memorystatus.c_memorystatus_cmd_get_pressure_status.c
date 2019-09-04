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
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  PRIV_VM_PRESSURE ; 
 scalar_t__ kVMPressureNormal ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 scalar_t__ memorystatus_vm_pressure_level ; 
 int priv_check_cred (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
memorystatus_cmd_get_pressure_status(int32_t *retval) {	
	int error;
	
	/* Need privilege for check */
	error = priv_check_cred(kauth_cred_get(), PRIV_VM_PRESSURE, 0);
	if (error) {
		return (error);
	}
	
	/* Inherently racy, so it's not worth taking a lock here */
	*retval = (kVMPressureNormal != memorystatus_vm_pressure_level) ? 1 : 0;
	
	return error;
}