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
typedef  int /*<<< orphan*/  u8 ;
struct efx_nic {int dummy; } ;
struct efx_mcdi_iface {int /*<<< orphan*/  iface_lock; int /*<<< orphan*/  seqno; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ EFX_REV_SIENA_A0 ; 
 struct efx_mcdi_iface* efx_mcdi (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_mcdi_acquire (struct efx_mcdi_iface*) ; 
 int /*<<< orphan*/  efx_mcdi_copyin (struct efx_nic*,unsigned int,int /*<<< orphan*/  const*,size_t) ; 
 scalar_t__ efx_nic_rev (struct efx_nic*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void efx_mcdi_rpc_start(struct efx_nic *efx, unsigned cmd, const u8 *inbuf,
			size_t inlen)
{
	struct efx_mcdi_iface *mcdi = efx_mcdi(efx);

	BUG_ON(efx_nic_rev(efx) < EFX_REV_SIENA_A0);

	efx_mcdi_acquire(mcdi);

	/* Serialise with efx_mcdi_ev_cpl() and efx_mcdi_ev_death() */
	spin_lock_bh(&mcdi->iface_lock);
	++mcdi->seqno;
	spin_unlock_bh(&mcdi->iface_lock);

	efx_mcdi_copyin(efx, cmd, inbuf, inlen);
}