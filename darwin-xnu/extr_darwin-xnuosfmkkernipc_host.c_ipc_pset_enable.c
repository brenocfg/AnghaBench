#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* processor_set_t ;
typedef  int /*<<< orphan*/  ipc_kobject_t ;
struct TYPE_3__ {int /*<<< orphan*/  pset_name_self; int /*<<< orphan*/  pset_self; } ;

/* Variables and functions */
 int /*<<< orphan*/  IKOT_PSET ; 
 int /*<<< orphan*/  IKOT_PSET_NAME ; 
 int /*<<< orphan*/  ipc_kobject_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ipc_pset_enable(
	processor_set_t		pset)
{
	ipc_kobject_set(pset->pset_self, (ipc_kobject_t) pset, IKOT_PSET);
	ipc_kobject_set(pset->pset_name_self, (ipc_kobject_t) pset, IKOT_PSET_NAME);
}