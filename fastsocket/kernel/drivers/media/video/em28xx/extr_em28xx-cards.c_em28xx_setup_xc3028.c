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
struct xc2028_ctrl {int max_len; void* demod; void* fname; int /*<<< orphan*/  mts; } ;
struct em28xx {size_t model; } ;
struct TYPE_2__ {int /*<<< orphan*/  mts_firmware; } ;

/* Variables and functions */
#define  EM2880_BOARD_AMD_ATI_TV_WONDER_HD_600 142 
#define  EM2880_BOARD_EMPIRE_DUAL_TV 141 
#define  EM2880_BOARD_HAUPPAUGE_WINTV_HVR_900 140 
#define  EM2880_BOARD_HAUPPAUGE_WINTV_HVR_900_R2 139 
#define  EM2880_BOARD_PINNACLE_PCTV_HD_PRO 138 
#define  EM2880_BOARD_TERRATEC_HYBRID_XS 137 
#define  EM2880_BOARD_TERRATEC_HYBRID_XS_FR 136 
#define  EM2881_BOARD_PINNACLE_HYBRID_PRO 135 
#define  EM2882_BOARD_DIKOM_DK300 134 
#define  EM2882_BOARD_EVGA_INDTUBE 133 
#define  EM2882_BOARD_KWORLD_VS_DVBT 132 
#define  EM2882_BOARD_TERRATEC_HYBRID_XS 131 
#define  EM2883_BOARD_HAUPPAUGE_WINTV_HVR_850 130 
#define  EM2883_BOARD_HAUPPAUGE_WINTV_HVR_950 129 
#define  EM2883_BOARD_KWORLD_HYBRID_330U 128 
 void* XC2028_DEFAULT_FIRMWARE ; 
 void* XC3028L_DEFAULT_FIRMWARE ; 
 void* XC3028_FE_CHINA ; 
 void* XC3028_FE_DEFAULT ; 
 void* XC3028_FE_OREN538 ; 
 void* XC3028_FE_ZARLINK456 ; 
 TYPE_1__* em28xx_boards ; 
 int /*<<< orphan*/  memset (struct xc2028_ctrl*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void em28xx_setup_xc3028(struct em28xx *dev, struct xc2028_ctrl *ctl)
{
	memset(ctl, 0, sizeof(*ctl));

	ctl->fname   = XC2028_DEFAULT_FIRMWARE;
	ctl->max_len = 64;
	ctl->mts = em28xx_boards[dev->model].mts_firmware;

	switch (dev->model) {
	case EM2880_BOARD_EMPIRE_DUAL_TV:
	case EM2880_BOARD_HAUPPAUGE_WINTV_HVR_900:
	case EM2882_BOARD_TERRATEC_HYBRID_XS:
		ctl->demod = XC3028_FE_ZARLINK456;
		break;
	case EM2880_BOARD_TERRATEC_HYBRID_XS:
	case EM2880_BOARD_TERRATEC_HYBRID_XS_FR:
	case EM2881_BOARD_PINNACLE_HYBRID_PRO:
		ctl->demod = XC3028_FE_ZARLINK456;
		break;
	case EM2880_BOARD_HAUPPAUGE_WINTV_HVR_900_R2:
		/* djh - Not sure which demod we need here */
		ctl->demod = XC3028_FE_DEFAULT;
		break;
	case EM2880_BOARD_AMD_ATI_TV_WONDER_HD_600:
		ctl->demod = XC3028_FE_DEFAULT;
		ctl->fname = XC3028L_DEFAULT_FIRMWARE;
		break;
	case EM2883_BOARD_HAUPPAUGE_WINTV_HVR_850:
	case EM2883_BOARD_HAUPPAUGE_WINTV_HVR_950:
	case EM2880_BOARD_PINNACLE_PCTV_HD_PRO:
		/* FIXME: Better to specify the needed IF */
		ctl->demod = XC3028_FE_DEFAULT;
		break;
	case EM2883_BOARD_KWORLD_HYBRID_330U:
	case EM2882_BOARD_DIKOM_DK300:
	case EM2882_BOARD_KWORLD_VS_DVBT:
		ctl->demod = XC3028_FE_CHINA;
		ctl->fname = XC2028_DEFAULT_FIRMWARE;
		break;
	case EM2882_BOARD_EVGA_INDTUBE:
		ctl->demod = XC3028_FE_CHINA;
		ctl->fname = XC3028L_DEFAULT_FIRMWARE;
		break;
	default:
		ctl->demod = XC3028_FE_OREN538;
	}
}