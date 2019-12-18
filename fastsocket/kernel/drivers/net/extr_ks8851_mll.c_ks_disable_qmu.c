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
typedef  int /*<<< orphan*/  u16 ;
struct ks_net {int enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  KS_RXCR1 ; 
 int /*<<< orphan*/  KS_TXCR ; 
 int /*<<< orphan*/  RXCR1_RXE ; 
 int /*<<< orphan*/  TXCR_TXE ; 
 int /*<<< orphan*/  ks_rdreg16 (struct ks_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks_wrreg16 (struct ks_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ks_disable_qmu(struct ks_net *ks)
{
	u16	w;

	w = ks_rdreg16(ks, KS_TXCR);

	/* Disables QMU Transmit (TXCR). */
	w  &= ~TXCR_TXE;
	ks_wrreg16(ks, KS_TXCR, w);

	/* Disables QMU Receive (RXCR1). */
	w = ks_rdreg16(ks, KS_RXCR1);
	w &= ~RXCR1_RXE ;
	ks_wrreg16(ks, KS_RXCR1, w);

	ks->enabled = false;

}