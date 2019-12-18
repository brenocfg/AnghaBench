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
typedef  int /*<<< orphan*/  u16 ;
struct ssb_sprom {int revision; scalar_t__ il0mac; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int /*<<< orphan*/  a3; int /*<<< orphan*/  a2; int /*<<< orphan*/  a1; int /*<<< orphan*/  a0; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPEX (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int SPOFF (int /*<<< orphan*/ ) ; 
 int SSB_SPROM4_AGAIN0 ; 
 int /*<<< orphan*/  SSB_SPROM4_AGAIN01 ; 
 int SSB_SPROM4_AGAIN0_SHIFT ; 
 int SSB_SPROM4_AGAIN1 ; 
 int SSB_SPROM4_AGAIN1_SHIFT ; 
 int SSB_SPROM4_AGAIN2 ; 
 int /*<<< orphan*/  SSB_SPROM4_AGAIN23 ; 
 int SSB_SPROM4_AGAIN2_SHIFT ; 
 int SSB_SPROM4_AGAIN3 ; 
 int SSB_SPROM4_AGAIN3_SHIFT ; 
 int /*<<< orphan*/  SSB_SPROM4_ANTAVAIL ; 
 int SSB_SPROM4_ANTAVAIL_A ; 
 int SSB_SPROM4_ANTAVAIL_A_SHIFT ; 
 int SSB_SPROM4_ANTAVAIL_BG ; 
 int SSB_SPROM4_ANTAVAIL_BG_SHIFT ; 
 int /*<<< orphan*/  SSB_SPROM4_BFL2HI ; 
 int /*<<< orphan*/  SSB_SPROM4_BFL2LO ; 
 int /*<<< orphan*/  SSB_SPROM4_BFLHI ; 
 int /*<<< orphan*/  SSB_SPROM4_BFLLO ; 
 int /*<<< orphan*/  SSB_SPROM4_BOARDREV ; 
 int /*<<< orphan*/  SSB_SPROM4_CCODE ; 
 int /*<<< orphan*/  SSB_SPROM4_ETHPHY ; 
 int SSB_SPROM4_ETHPHY_ET0A ; 
 int SSB_SPROM4_ETHPHY_ET1A ; 
 int SSB_SPROM4_ETHPHY_ET1A_SHIFT ; 
 int /*<<< orphan*/  SSB_SPROM4_GPIOA ; 
 int SSB_SPROM4_GPIOA_P0 ; 
 int SSB_SPROM4_GPIOA_P1 ; 
 int SSB_SPROM4_GPIOA_P1_SHIFT ; 
 int /*<<< orphan*/  SSB_SPROM4_GPIOB ; 
 int SSB_SPROM4_GPIOB_P2 ; 
 int SSB_SPROM4_GPIOB_P3 ; 
 int SSB_SPROM4_GPIOB_P3_SHIFT ; 
 int /*<<< orphan*/  SSB_SPROM4_IL0MAC ; 
 int SSB_SPROM4_ITSSI_A ; 
 int SSB_SPROM4_ITSSI_A_SHIFT ; 
 int SSB_SPROM4_ITSSI_BG ; 
 int SSB_SPROM4_ITSSI_BG_SHIFT ; 
 int /*<<< orphan*/  SSB_SPROM4_MAXP_A ; 
 int SSB_SPROM4_MAXP_A_MASK ; 
 int /*<<< orphan*/  SSB_SPROM4_MAXP_BG ; 
 int SSB_SPROM4_MAXP_BG_MASK ; 
 int /*<<< orphan*/  SSB_SPROM5_BFL2HI ; 
 int /*<<< orphan*/  SSB_SPROM5_BFL2LO ; 
 int /*<<< orphan*/  SSB_SPROM5_BFLHI ; 
 int /*<<< orphan*/  SSB_SPROM5_BFLLO ; 
 int /*<<< orphan*/  SSB_SPROM5_CCODE ; 
 int /*<<< orphan*/  SSB_SPROM5_GPIOA ; 
 int SSB_SPROM5_GPIOA_P0 ; 
 int SSB_SPROM5_GPIOA_P1 ; 
 int SSB_SPROM5_GPIOA_P1_SHIFT ; 
 int /*<<< orphan*/  SSB_SPROM5_GPIOB ; 
 int SSB_SPROM5_GPIOB_P2 ; 
 int SSB_SPROM5_GPIOB_P3 ; 
 int SSB_SPROM5_GPIOB_P3_SHIFT ; 
 int /*<<< orphan*/  SSB_SPROM5_IL0MAC ; 
 int /*<<< orphan*/ * alpha2 ; 
 int /*<<< orphan*/  ant_available_a ; 
 int /*<<< orphan*/  ant_available_bg ; 
 TYPE_1__ antenna_gain ; 
 int /*<<< orphan*/  board_rev ; 
 int /*<<< orphan*/  boardflags2_hi ; 
 int /*<<< orphan*/  boardflags2_lo ; 
 int /*<<< orphan*/  boardflags_hi ; 
 int /*<<< orphan*/  boardflags_lo ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  et0phyaddr ; 
 int /*<<< orphan*/  et1phyaddr ; 
 int /*<<< orphan*/  gpio0 ; 
 int /*<<< orphan*/  gpio1 ; 
 int /*<<< orphan*/  gpio2 ; 
 int /*<<< orphan*/  gpio3 ; 
 int /*<<< orphan*/  itssi_a ; 
 int /*<<< orphan*/  itssi_bg ; 
 int /*<<< orphan*/  maxpwr_a ; 
 int /*<<< orphan*/  maxpwr_bg ; 
 int /*<<< orphan*/  sprom_extract_r458 (struct ssb_sprom*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void sprom_extract_r45(struct ssb_sprom *out, const u16 *in)
{
	int i;
	u16 v;
	u16 il0mac_offset;

	if (out->revision == 4)
		il0mac_offset = SSB_SPROM4_IL0MAC;
	else
		il0mac_offset = SSB_SPROM5_IL0MAC;
	/* extract the MAC address */
	for (i = 0; i < 3; i++) {
		v = in[SPOFF(il0mac_offset) + i];
		*(((__be16 *)out->il0mac) + i) = cpu_to_be16(v);
	}
	SPEX(et0phyaddr, SSB_SPROM4_ETHPHY, SSB_SPROM4_ETHPHY_ET0A, 0);
	SPEX(et1phyaddr, SSB_SPROM4_ETHPHY, SSB_SPROM4_ETHPHY_ET1A,
	     SSB_SPROM4_ETHPHY_ET1A_SHIFT);
	SPEX(board_rev, SSB_SPROM4_BOARDREV, 0xFFFF, 0);
	if (out->revision == 4) {
		SPEX(alpha2[0], SSB_SPROM4_CCODE, 0xff00, 8);
		SPEX(alpha2[1], SSB_SPROM4_CCODE, 0x00ff, 0);
		SPEX(boardflags_lo, SSB_SPROM4_BFLLO, 0xFFFF, 0);
		SPEX(boardflags_hi, SSB_SPROM4_BFLHI, 0xFFFF, 0);
		SPEX(boardflags2_lo, SSB_SPROM4_BFL2LO, 0xFFFF, 0);
		SPEX(boardflags2_hi, SSB_SPROM4_BFL2HI, 0xFFFF, 0);
	} else {
		SPEX(alpha2[0], SSB_SPROM5_CCODE, 0xff00, 8);
		SPEX(alpha2[1], SSB_SPROM5_CCODE, 0x00ff, 0);
		SPEX(boardflags_lo, SSB_SPROM5_BFLLO, 0xFFFF, 0);
		SPEX(boardflags_hi, SSB_SPROM5_BFLHI, 0xFFFF, 0);
		SPEX(boardflags2_lo, SSB_SPROM5_BFL2LO, 0xFFFF, 0);
		SPEX(boardflags2_hi, SSB_SPROM5_BFL2HI, 0xFFFF, 0);
	}
	SPEX(ant_available_a, SSB_SPROM4_ANTAVAIL, SSB_SPROM4_ANTAVAIL_A,
	     SSB_SPROM4_ANTAVAIL_A_SHIFT);
	SPEX(ant_available_bg, SSB_SPROM4_ANTAVAIL, SSB_SPROM4_ANTAVAIL_BG,
	     SSB_SPROM4_ANTAVAIL_BG_SHIFT);
	SPEX(maxpwr_bg, SSB_SPROM4_MAXP_BG, SSB_SPROM4_MAXP_BG_MASK, 0);
	SPEX(itssi_bg, SSB_SPROM4_MAXP_BG, SSB_SPROM4_ITSSI_BG,
	     SSB_SPROM4_ITSSI_BG_SHIFT);
	SPEX(maxpwr_a, SSB_SPROM4_MAXP_A, SSB_SPROM4_MAXP_A_MASK, 0);
	SPEX(itssi_a, SSB_SPROM4_MAXP_A, SSB_SPROM4_ITSSI_A,
	     SSB_SPROM4_ITSSI_A_SHIFT);
	if (out->revision == 4) {
		SPEX(gpio0, SSB_SPROM4_GPIOA, SSB_SPROM4_GPIOA_P0, 0);
		SPEX(gpio1, SSB_SPROM4_GPIOA, SSB_SPROM4_GPIOA_P1,
		     SSB_SPROM4_GPIOA_P1_SHIFT);
		SPEX(gpio2, SSB_SPROM4_GPIOB, SSB_SPROM4_GPIOB_P2, 0);
		SPEX(gpio3, SSB_SPROM4_GPIOB, SSB_SPROM4_GPIOB_P3,
		     SSB_SPROM4_GPIOB_P3_SHIFT);
	} else {
		SPEX(gpio0, SSB_SPROM5_GPIOA, SSB_SPROM5_GPIOA_P0, 0);
		SPEX(gpio1, SSB_SPROM5_GPIOA, SSB_SPROM5_GPIOA_P1,
		     SSB_SPROM5_GPIOA_P1_SHIFT);
		SPEX(gpio2, SSB_SPROM5_GPIOB, SSB_SPROM5_GPIOB_P2, 0);
		SPEX(gpio3, SSB_SPROM5_GPIOB, SSB_SPROM5_GPIOB_P3,
		     SSB_SPROM5_GPIOB_P3_SHIFT);
	}

	/* Extract the antenna gain values. */
	SPEX(antenna_gain.a0, SSB_SPROM4_AGAIN01,
	     SSB_SPROM4_AGAIN0, SSB_SPROM4_AGAIN0_SHIFT);
	SPEX(antenna_gain.a1, SSB_SPROM4_AGAIN01,
	     SSB_SPROM4_AGAIN1, SSB_SPROM4_AGAIN1_SHIFT);
	SPEX(antenna_gain.a2, SSB_SPROM4_AGAIN23,
	     SSB_SPROM4_AGAIN2, SSB_SPROM4_AGAIN2_SHIFT);
	SPEX(antenna_gain.a3, SSB_SPROM4_AGAIN23,
	     SSB_SPROM4_AGAIN3, SSB_SPROM4_AGAIN3_SHIFT);

	sprom_extract_r458(out, in);

	/* TODO - get remaining rev 4 stuff needed */
}