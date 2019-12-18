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
struct efx_nic {int dummy; } ;
struct efx_mcdi_iface {int /*<<< orphan*/  mode; int /*<<< orphan*/  state; int /*<<< orphan*/  iface_lock; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 scalar_t__ EFX_REV_SIENA_A0 ; 
 int /*<<< orphan*/  MCDI_MODE_POLL ; 
 int /*<<< orphan*/  MCDI_STATE_QUIESCENT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct efx_mcdi_iface* efx_mcdi (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_mcdi_poll_reboot (struct efx_nic*) ; 
 scalar_t__ efx_nic_rev (struct efx_nic*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void efx_mcdi_init(struct efx_nic *efx)
{
	struct efx_mcdi_iface *mcdi;

	if (efx_nic_rev(efx) < EFX_REV_SIENA_A0)
		return;

	mcdi = efx_mcdi(efx);
	init_waitqueue_head(&mcdi->wq);
	spin_lock_init(&mcdi->iface_lock);
	atomic_set(&mcdi->state, MCDI_STATE_QUIESCENT);
	mcdi->mode = MCDI_MODE_POLL;

	(void) efx_mcdi_poll_reboot(efx);
}