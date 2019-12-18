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
typedef  TYPE_1__* mig_object_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_4__ {int /*<<< orphan*/  port; int /*<<< orphan*/  const* pVtbl; } ;
typedef  int /*<<< orphan*/  IMIGObjectVtbl ;
typedef  int /*<<< orphan*/  IMIGObject ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_PORT_NULL ; 
 TYPE_1__* MIG_OBJECT_NULL ; 

kern_return_t
mig_object_init(
	mig_object_t		mig_object,
	const IMIGObject	*interface)
{
	if (mig_object == MIG_OBJECT_NULL)
		return KERN_INVALID_ARGUMENT;
	mig_object->pVtbl = (const IMIGObjectVtbl *)interface;
	mig_object->port = MACH_PORT_NULL;
	return KERN_SUCCESS;
}