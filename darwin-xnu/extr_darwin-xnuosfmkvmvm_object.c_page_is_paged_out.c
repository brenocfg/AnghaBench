#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_object_t ;
typedef  int /*<<< orphan*/  vm_object_offset_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {scalar_t__ pager_ready; int /*<<< orphan*/  terminating; scalar_t__ alive; scalar_t__ internal; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ VM_COMPRESSOR_PAGER_STATE_GET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ VM_EXTERNAL_STATE_EXISTS ; 

__attribute__((used)) static boolean_t
page_is_paged_out(
	vm_object_t		object,
	vm_object_offset_t	offset)
{
	if (object->internal &&
	   object->alive &&
	   !object->terminating &&
	   object->pager_ready) {

		if (VM_COMPRESSOR_PAGER_STATE_GET(object, offset) 
		    == VM_EXTERNAL_STATE_EXISTS) {
			return TRUE;
		}
	}
	return FALSE;
}