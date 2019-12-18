#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct efx_nic {scalar_t__ state; TYPE_1__* type; int /*<<< orphan*/  reset_work; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* fini ) (struct efx_nic*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ STATE_READY ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_fini_napi (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_fini_port (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_nic_fini_interrupt (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_remove_all (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_stop_interrupts (struct efx_nic*,int) ; 
 int /*<<< orphan*/  stub1 (struct efx_nic*) ; 

__attribute__((used)) static void efx_pci_remove_main(struct efx_nic *efx)
{
	/* Flush reset_work. It can no longer be scheduled since we
	 * are not READY.
	 */
	BUG_ON(efx->state == STATE_READY);
	cancel_work_sync(&efx->reset_work);

	efx_stop_interrupts(efx, false);
	efx_nic_fini_interrupt(efx);
	efx_fini_port(efx);
	efx->type->fini(efx);
	efx_fini_napi(efx);
	efx_remove_all(efx);
}