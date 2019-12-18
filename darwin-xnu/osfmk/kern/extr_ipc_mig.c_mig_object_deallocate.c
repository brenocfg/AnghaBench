#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* mig_object_t ;
struct TYPE_6__ {TYPE_1__* pVtbl; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* Release ) (int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  IMIGObject ;

/* Variables and functions */
 TYPE_2__* MIG_OBJECT_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void
mig_object_deallocate(
	mig_object_t	mig_object)
{
	assert(mig_object != MIG_OBJECT_NULL);
	mig_object->pVtbl->Release((IMIGObject *)mig_object);
}