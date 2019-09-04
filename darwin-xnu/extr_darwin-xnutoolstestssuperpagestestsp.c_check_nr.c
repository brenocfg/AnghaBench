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
typedef  int mach_vm_size_t ;
typedef  scalar_t__ mach_vm_address_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  check_r (scalar_t__,int,int*) ; 
 int /*<<< orphan*/  error ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 

boolean_t
check_nr(mach_vm_address_t addr, mach_vm_size_t size, int *res) {
	int i;
	boolean_t ret;
	for (i=0; i<size/PAGE_SIZE; i++) {
		if ((ret = check_r(addr+i*PAGE_SIZE, PAGE_SIZE, res))) {
			sprintf(error, "page still readable");
			return FALSE;
		}
	}
	return TRUE;
}