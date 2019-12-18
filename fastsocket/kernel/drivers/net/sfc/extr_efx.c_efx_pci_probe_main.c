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
struct efx_nic {TYPE_1__* type; int /*<<< orphan*/  net_dev; } ;
struct TYPE_2__ {int (* init ) (struct efx_nic*) ;int /*<<< orphan*/  (* fini ) (struct efx_nic*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  efx_fini_napi (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_fini_port (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_init_napi (struct efx_nic*) ; 
 int efx_init_port (struct efx_nic*) ; 
 int efx_nic_init_interrupt (struct efx_nic*) ; 
 int efx_probe_all (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_remove_all (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_start_interrupts (struct efx_nic*,int) ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  probe ; 
 int stub1 (struct efx_nic*) ; 
 int /*<<< orphan*/  stub2 (struct efx_nic*) ; 

__attribute__((used)) static int efx_pci_probe_main(struct efx_nic *efx)
{
	int rc;

	/* Do start-of-day initialisation */
	rc = efx_probe_all(efx);
	if (rc)
		goto fail1;

	efx_init_napi(efx);

	rc = efx->type->init(efx);
	if (rc) {
		netif_err(efx, probe, efx->net_dev,
			  "failed to initialise NIC\n");
		goto fail3;
	}

	rc = efx_init_port(efx);
	if (rc) {
		netif_err(efx, probe, efx->net_dev,
			  "failed to initialise port\n");
		goto fail4;
	}

	rc = efx_nic_init_interrupt(efx);
	if (rc)
		goto fail5;
	efx_start_interrupts(efx, false);

	return 0;

 fail5:
	efx_fini_port(efx);
 fail4:
	efx->type->fini(efx);
 fail3:
	efx_fini_napi(efx);
	efx_remove_all(efx);
 fail1:
	return rc;
}