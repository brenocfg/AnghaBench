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
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ ml_validate_nofault (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  paniclog_append_noflush (char*,char const*,...) ; 

__attribute__((used)) static boolean_t validate_ptr(
	vm_offset_t ptr, vm_size_t size, const char * ptr_name)
{
	if (ptr) {
		if (ml_validate_nofault(ptr, size)) {
			return TRUE;
		} else {
			paniclog_append_noflush("Invalid %s pointer: %p size: %d\n",
				ptr_name, (void *)ptr, (int)size);
			return FALSE;
		}
	} else {
		paniclog_append_noflush("NULL %s pointer\n", ptr_name);
		return FALSE;
	}
}