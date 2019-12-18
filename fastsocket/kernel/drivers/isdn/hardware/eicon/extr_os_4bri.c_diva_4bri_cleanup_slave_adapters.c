#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * object; } ;
struct TYPE_6__ {int tasks; scalar_t__ e_count; scalar_t__ e_max; int /*<<< orphan*/ * e_tbl; TYPE_3__ isr_soft_isr; TYPE_3__ req_soft_isr; int /*<<< orphan*/  data_spin_lock; int /*<<< orphan*/  isr_spin_lock; } ;
struct TYPE_7__ {TYPE_1__ xdi_adapter; struct TYPE_7__** slave_adapters; } ;
typedef  TYPE_2__ diva_os_xdi_adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  diva_os_cancel_soft_isr (TYPE_3__*) ; 
 int /*<<< orphan*/  diva_os_destroy_spin_lock (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  diva_os_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  diva_os_remove_soft_isr (TYPE_3__*) ; 

__attribute__((used)) static int diva_4bri_cleanup_slave_adapters(diva_os_xdi_adapter_t * a)
{
	diva_os_xdi_adapter_t *adapter_list[4];
	diva_os_xdi_adapter_t *diva_current;
	int i;

	adapter_list[0] = a;
	adapter_list[1] = a->slave_adapters[0];
	adapter_list[2] = a->slave_adapters[1];
	adapter_list[3] = a->slave_adapters[2];

	for (i = 0; i < a->xdi_adapter.tasks; i++) {
		diva_current = adapter_list[i];
		if (diva_current) {
			diva_os_destroy_spin_lock(&diva_current->
						  xdi_adapter.
						  isr_spin_lock, "unload");
			diva_os_destroy_spin_lock(&diva_current->
						  xdi_adapter.
						  data_spin_lock,
						  "unload");

			diva_os_cancel_soft_isr(&diva_current->xdi_adapter.
						req_soft_isr);
			diva_os_cancel_soft_isr(&diva_current->xdi_adapter.
						isr_soft_isr);

			diva_os_remove_soft_isr(&diva_current->xdi_adapter.
						req_soft_isr);
			diva_current->xdi_adapter.isr_soft_isr.object = NULL;

			if (diva_current->xdi_adapter.e_tbl) {
				diva_os_free(0,
					     diva_current->xdi_adapter.
					     e_tbl);
			}
			diva_current->xdi_adapter.e_tbl = NULL;
			diva_current->xdi_adapter.e_max = 0;
			diva_current->xdi_adapter.e_count = 0;
		}
	}

	return (0);
}