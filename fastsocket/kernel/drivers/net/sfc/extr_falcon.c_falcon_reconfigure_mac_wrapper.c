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
struct efx_link_state {int speed; int /*<<< orphan*/  up; } ;
struct efx_nic {int /*<<< orphan*/  promiscuous; int /*<<< orphan*/  reset_pending; struct efx_link_state link_state; } ;
typedef  int /*<<< orphan*/  efx_oword_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACCESS_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFX_POPULATE_OWORD_5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ EFX_REV_FALCON_B0 ; 
 int /*<<< orphan*/  EFX_SET_OWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FRF_AB_MAC_BCAD_ACPT ; 
 int /*<<< orphan*/  FRF_AB_MAC_LINK_STATUS ; 
 int /*<<< orphan*/  FRF_AB_MAC_SPEED ; 
 int /*<<< orphan*/  FRF_AB_MAC_UC_PROM ; 
 int /*<<< orphan*/  FRF_AB_MAC_XOFF_VAL ; 
 int /*<<< orphan*/  FRF_AZ_RX_XOFF_MAC_EN ; 
 int /*<<< orphan*/  FRF_BB_TXFIFO_DRAIN_EN ; 
 int /*<<< orphan*/  FRF_BZ_RX_INGR_EN ; 
 int /*<<< orphan*/  FR_AB_MAC_CTRL ; 
 int /*<<< orphan*/  FR_AZ_RX_CFG ; 
 scalar_t__ efx_nic_rev (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_reado (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_writeo (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  falcon_push_multicast_hash (struct efx_nic*) ; 

void falcon_reconfigure_mac_wrapper(struct efx_nic *efx)
{
	struct efx_link_state *link_state = &efx->link_state;
	efx_oword_t reg;
	int link_speed, isolate;

	isolate = !!ACCESS_ONCE(efx->reset_pending);

	switch (link_state->speed) {
	case 10000: link_speed = 3; break;
	case 1000:  link_speed = 2; break;
	case 100:   link_speed = 1; break;
	default:    link_speed = 0; break;
	}
	/* MAC_LINK_STATUS controls MAC backpressure but doesn't work
	 * as advertised.  Disable to ensure packets are not
	 * indefinitely held and TX queue can be flushed at any point
	 * while the link is down. */
	EFX_POPULATE_OWORD_5(reg,
			     FRF_AB_MAC_XOFF_VAL, 0xffff /* max pause time */,
			     FRF_AB_MAC_BCAD_ACPT, 1,
			     FRF_AB_MAC_UC_PROM, efx->promiscuous,
			     FRF_AB_MAC_LINK_STATUS, 1, /* always set */
			     FRF_AB_MAC_SPEED, link_speed);
	/* On B0, MAC backpressure can be disabled and packets get
	 * discarded. */
	if (efx_nic_rev(efx) >= EFX_REV_FALCON_B0) {
		EFX_SET_OWORD_FIELD(reg, FRF_BB_TXFIFO_DRAIN_EN,
				    !link_state->up || isolate);
	}

	efx_writeo(efx, &reg, FR_AB_MAC_CTRL);

	/* Restore the multicast hash registers. */
	falcon_push_multicast_hash(efx);

	efx_reado(efx, &reg, FR_AZ_RX_CFG);
	/* Enable XOFF signal from RX FIFO (we enabled it during NIC
	 * initialisation but it may read back as 0) */
	EFX_SET_OWORD_FIELD(reg, FRF_AZ_RX_XOFF_MAC_EN, 1);
	/* Unisolate the MAC -> RX */
	if (efx_nic_rev(efx) >= EFX_REV_FALCON_B0)
		EFX_SET_OWORD_FIELD(reg, FRF_BZ_RX_INGR_EN, !isolate);
	efx_writeo(efx, &reg, FR_AZ_RX_CFG);
}