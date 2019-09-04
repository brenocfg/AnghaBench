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
typedef  scalar_t__ mach_vm_size_t ;
typedef  int /*<<< orphan*/  mach_vm_address_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ SUPERPAGE_SIZE ; 
 int TRUE ; 
 int check_r (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int check_w (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  error ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 

boolean_t
check_rw(mach_vm_address_t addr, mach_vm_size_t size) {
	int ret;
	int res;
	if (!(ret = check_w(addr, size))) return ret;
	if (!(ret = check_r(addr, size, &res))) return ret;
	if ((size==SUPERPAGE_SIZE) && (res!=0xfff00000)) {
		sprintf(error, "checksum error");
		return FALSE;
	}

	return TRUE;
}