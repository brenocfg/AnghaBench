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
typedef  scalar_t__ vm_object_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  scan_object_collision ; 
 scalar_t__ vm_pageout_scan_wants_object ; 

boolean_t
vm_object_lock_avoid(vm_object_t object)
{
        if (object == vm_pageout_scan_wants_object) {
	        scan_object_collision++;
		return TRUE;
	}
	return FALSE;
}