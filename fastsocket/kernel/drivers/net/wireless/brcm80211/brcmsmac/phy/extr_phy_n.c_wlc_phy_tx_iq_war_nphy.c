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
struct nphy_iq_comp {int /*<<< orphan*/  b1; int /*<<< orphan*/  a1; int /*<<< orphan*/  b0; int /*<<< orphan*/  a0; } ;
struct brcms_phy {TYPE_1__* sh; } ;
struct TYPE_2__ {int /*<<< orphan*/  physhim; } ;

/* Variables and functions */
 scalar_t__ M_20IN40_IQ ; 
 int /*<<< orphan*/  wlapi_bmac_write_shm (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_table_read_nphy (struct brcms_phy*,int,int,int,int,struct nphy_iq_comp*) ; 

__attribute__((used)) static void wlc_phy_tx_iq_war_nphy(struct brcms_phy *pi)
{
	struct nphy_iq_comp tx_comp;

	wlc_phy_table_read_nphy(pi, 15, 4, 0x50, 16, &tx_comp);

	wlapi_bmac_write_shm(pi->sh->physhim, M_20IN40_IQ, tx_comp.a0);
	wlapi_bmac_write_shm(pi->sh->physhim, M_20IN40_IQ + 2, tx_comp.b0);
	wlapi_bmac_write_shm(pi->sh->physhim, M_20IN40_IQ + 4, tx_comp.a1);
	wlapi_bmac_write_shm(pi->sh->physhim, M_20IN40_IQ + 6, tx_comp.b1);
}