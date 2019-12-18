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
typedef  int /*<<< orphan*/  mach_vm_size_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  SUPERPAGE_SIZE ; 
 int TRUE ; 
 int check_kr (int,char*) ; 
 int check_nr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error ; 
 int /*<<< orphan*/  global_addr ; 
 int /*<<< orphan*/  global_size ; 
 int /*<<< orphan*/  mach_task_self () ; 
 int mach_vm_deallocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 

boolean_t
test_deallocate() {
	mach_vm_size_t	size = SUPERPAGE_SIZE;
	int kr, ret;

	if (!global_addr) {
		sprintf(error, "skipped deallocation");
		return FALSE;
	}
	kr = mach_vm_deallocate(mach_task_self(), global_addr, global_size);
	if (!(ret = check_kr(kr, "mach_vm_deallocate"))) return ret;
	if (!(ret = check_nr(global_addr, size, NULL))) return ret;
	return TRUE;
}