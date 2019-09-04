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
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  error ; 
 int /*<<< orphan*/  resume ; 
 int setjmp (int /*<<< orphan*/ ) ; 
 char** signame ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 

boolean_t
check_r(mach_vm_address_t addr, mach_vm_size_t size, int *res) {
	volatile char *data = (char*)(uintptr_t)addr;
	int i, sig, test;
	
	if ((sig = setjmp(resume)) != 0) {
		sprintf(error, "%s when reading", signame[sig]);
		return FALSE;
	}
	test = 0;
	for (i=0; i<size; i++)
		test += (data)[i];

	if (res)
		*res = test;
	
	return TRUE;
}