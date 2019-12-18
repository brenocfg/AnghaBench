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
struct efx_nic {int /*<<< orphan*/  net_dev; } ;
struct efx_mcdi_iface {unsigned int seqno; unsigned int resprc; unsigned int resplen; int /*<<< orphan*/  iface_lock; scalar_t__ credits; } ;

/* Variables and functions */
 unsigned int SEQ_MASK ; 
 struct efx_mcdi_iface* efx_mcdi (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_mcdi_complete (struct efx_mcdi_iface*) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void efx_mcdi_ev_cpl(struct efx_nic *efx, unsigned int seqno,
			    unsigned int datalen, unsigned int errno)
{
	struct efx_mcdi_iface *mcdi = efx_mcdi(efx);
	bool wake = false;

	spin_lock(&mcdi->iface_lock);

	if ((seqno ^ mcdi->seqno) & SEQ_MASK) {
		if (mcdi->credits)
			/* The request has been cancelled */
			--mcdi->credits;
		else
			netif_err(efx, hw, efx->net_dev,
				  "MC response mismatch tx seq 0x%x rx "
				  "seq 0x%x\n", seqno, mcdi->seqno);
	} else {
		mcdi->resprc = errno;
		mcdi->resplen = datalen;

		wake = true;
	}

	spin_unlock(&mcdi->iface_lock);

	if (wake)
		efx_mcdi_complete(mcdi);
}