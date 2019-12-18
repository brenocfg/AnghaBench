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
struct brcms_phy {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ BRCMS_N_PREAMBLE_GF ; 
 int /*<<< orphan*/  RX_GF_MM_AUTO ; 
 int /*<<< orphan*/  RX_GF_OR_MM ; 
 int /*<<< orphan*/  read_phy_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wlc_phy_update_mimoconfig_nphy(struct brcms_phy *pi, s32 preamble)
{
	bool gf_preamble = false;
	u16 val;

	if (preamble == BRCMS_N_PREAMBLE_GF)
		gf_preamble = true;

	val = read_phy_reg(pi, 0xed);

	val |= RX_GF_MM_AUTO;
	val &= ~RX_GF_OR_MM;
	if (gf_preamble)
		val |= RX_GF_OR_MM;

	write_phy_reg(pi, 0xed, val);
}