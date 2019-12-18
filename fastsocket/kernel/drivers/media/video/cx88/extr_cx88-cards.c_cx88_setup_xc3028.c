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
struct xc2028_ctrl {int max_len; int disable_power_mgmt; int mts; void* demod; int /*<<< orphan*/  fname; } ;
struct TYPE_2__ {int udelay; } ;
struct cx88_core {int boardnr; TYPE_1__ i2c_algo; } ;

/* Variables and functions */
#define  CX88_BOARD_DVICO_FUSIONHDTV_5_PCI_NANO 138 
#define  CX88_BOARD_DVICO_FUSIONHDTV_DVB_T_PRO 137 
#define  CX88_BOARD_GENIATECH_X8000_MT 136 
#define  CX88_BOARD_KWORLD_ATSC_120 135 
#define  CX88_BOARD_PINNACLE_HYBRID_PCTV 134 
#define  CX88_BOARD_POWERCOLOR_REAL_ANGEL 133 
#define  CX88_BOARD_PROLINK_PV_8000GT 132 
#define  CX88_BOARD_PROLINK_PV_GLOBAL_XTREME 131 
#define  CX88_BOARD_TERRATEC_CINERGY_HT_PCI_MKII 130 
#define  CX88_BOARD_WINFAST_DTV1800H 129 
#define  CX88_BOARD_WINFAST_TV2000_XP_GLOBAL 128 
 int /*<<< orphan*/  XC2028_DEFAULT_FIRMWARE ; 
 void* XC3028_FE_OREN538 ; 
 void* XC3028_FE_ZARLINK456 ; 
 int /*<<< orphan*/  memset (struct xc2028_ctrl*,int /*<<< orphan*/ ,int) ; 

void cx88_setup_xc3028(struct cx88_core *core, struct xc2028_ctrl *ctl)
{
	memset(ctl, 0, sizeof(*ctl));

	ctl->fname   = XC2028_DEFAULT_FIRMWARE;
	ctl->max_len = 64;

	switch (core->boardnr) {
	case CX88_BOARD_POWERCOLOR_REAL_ANGEL:
		/* Now works with firmware version 2.7 */
		if (core->i2c_algo.udelay < 16)
			core->i2c_algo.udelay = 16;
		break;
	case CX88_BOARD_DVICO_FUSIONHDTV_DVB_T_PRO:
	case CX88_BOARD_WINFAST_DTV1800H:
		ctl->demod = XC3028_FE_ZARLINK456;
		break;
	case CX88_BOARD_KWORLD_ATSC_120:
	case CX88_BOARD_DVICO_FUSIONHDTV_5_PCI_NANO:
		ctl->demod = XC3028_FE_OREN538;
		break;
	case CX88_BOARD_GENIATECH_X8000_MT:
		/* FIXME: For this board, the xc3028 never recovers after being
		   powered down (the reset GPIO probably is not set properly).
		   We don't have access to the hardware so we cannot determine
		   which GPIO is used for xc3028, so just disable power xc3028
		   power management for now */
		ctl->disable_power_mgmt = 1;
		break;
	case CX88_BOARD_WINFAST_TV2000_XP_GLOBAL:
	case CX88_BOARD_PROLINK_PV_GLOBAL_XTREME:
	case CX88_BOARD_PROLINK_PV_8000GT:
		/*
		 * Those boards uses non-MTS firmware
		 */
		break;
	case CX88_BOARD_PINNACLE_HYBRID_PCTV:
	case CX88_BOARD_TERRATEC_CINERGY_HT_PCI_MKII:
		ctl->demod = XC3028_FE_ZARLINK456;
		ctl->mts = 1;
		break;
	default:
		ctl->demod = XC3028_FE_OREN538;
		ctl->mts = 1;
	}
}