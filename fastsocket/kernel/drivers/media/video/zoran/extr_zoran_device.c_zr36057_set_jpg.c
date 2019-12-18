#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ hsync_pol; } ;
struct TYPE_6__ {int /*<<< orphan*/  type; TYPE_1__ vfe_pol; } ;
struct TYPE_5__ {int field_per_buff; int img_y; int img_height; int img_x; int img_width; scalar_t__ odd_even; } ;
struct zoran {TYPE_3__ card; int /*<<< orphan*/  stat_com; TYPE_2__ jpg_settings; struct tvnorm* timing; } ;
struct tvnorm {int Ht; int VStart; int HSyncStart; int Wt; int HStart; } ;
typedef  enum zoran_codec_mode { ____Placeholder_zoran_codec_mode } zoran_codec_mode ;

/* Variables and functions */
 int /*<<< orphan*/  BUZ ; 
#define  BUZ_MODE_MOTION_COMPRESS 131 
#define  BUZ_MODE_MOTION_DECOMPRESS 130 
#define  BUZ_MODE_STILL_COMPRESS 129 
#define  BUZ_MODE_STILL_DECOMPRESS 128 
 int /*<<< orphan*/  ZR36057_FHAP ; 
 int ZR36057_FHAP_NAX ; 
 int ZR36057_FHAP_PAX ; 
 int /*<<< orphan*/  ZR36057_FPP ; 
 int ZR36057_FPP_Odd_Even ; 
 int /*<<< orphan*/  ZR36057_FVAP ; 
 int ZR36057_FVAP_NAY ; 
 int ZR36057_FVAP_PAY ; 
 int /*<<< orphan*/  ZR36057_HSP ; 
 int ZR36057_HSP_HsyncStart ; 
 int ZR36057_HSP_LineTot ; 
 int /*<<< orphan*/  ZR36057_JCBA ; 
 int /*<<< orphan*/  ZR36057_JCFT ; 
 int /*<<< orphan*/  ZR36057_JMC ; 
 int ZR36057_JMC_Fld_per_buff ; 
 int ZR36057_JMC_JPG ; 
 int ZR36057_JMC_JPGCmpMode ; 
 int ZR36057_JMC_JPGExpMode ; 
 int ZR36057_JMC_MJPGCmpMode ; 
 int ZR36057_JMC_MJPGExpMode ; 
 int ZR36057_JMC_SyncMstr ; 
 int /*<<< orphan*/  ZR36057_JPC ; 
 int /*<<< orphan*/  ZR36057_VFEHCR ; 
 int /*<<< orphan*/  ZR36057_VFEHCR_HSPol ; 
 int /*<<< orphan*/  ZR36057_VFEVCR ; 
 int /*<<< orphan*/  ZR36057_VFEVCR_VSPol ; 
 int /*<<< orphan*/  ZR36057_VSP ; 
 int ZR36057_VSP_FrmTot ; 
 int ZR36057_VSP_VsyncSize ; 
 int /*<<< orphan*/  btand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btwrite (int,int /*<<< orphan*/ ) ; 
 int virt_to_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zr36057_adjust_vfe (struct zoran*,int) ; 

__attribute__((used)) static void
zr36057_set_jpg (struct zoran          *zr,
		 enum zoran_codec_mode  mode)
{
	struct tvnorm *tvn;
	u32 reg;

	tvn = zr->timing;

	/* assert P_Reset, disable code transfer, deassert Active */
	btwrite(0, ZR36057_JPC);

	/* MJPEG compression mode */
	switch (mode) {

	case BUZ_MODE_MOTION_COMPRESS:
	default:
		reg = ZR36057_JMC_MJPGCmpMode;
		break;

	case BUZ_MODE_MOTION_DECOMPRESS:
		reg = ZR36057_JMC_MJPGExpMode;
		reg |= ZR36057_JMC_SyncMstr;
		/* RJ: The following is experimental - improves the output to screen */
		//if(zr->jpg_settings.VFIFO_FB) reg |= ZR36057_JMC_VFIFO_FB; // No, it doesn't. SM
		break;

	case BUZ_MODE_STILL_COMPRESS:
		reg = ZR36057_JMC_JPGCmpMode;
		break;

	case BUZ_MODE_STILL_DECOMPRESS:
		reg = ZR36057_JMC_JPGExpMode;
		break;

	}
	reg |= ZR36057_JMC_JPG;
	if (zr->jpg_settings.field_per_buff == 1)
		reg |= ZR36057_JMC_Fld_per_buff;
	btwrite(reg, ZR36057_JMC);

	/* vertical */
	btor(ZR36057_VFEVCR_VSPol, ZR36057_VFEVCR);
	reg = (6 << ZR36057_VSP_VsyncSize) |
	      (tvn->Ht << ZR36057_VSP_FrmTot);
	btwrite(reg, ZR36057_VSP);
	reg = ((zr->jpg_settings.img_y + tvn->VStart) << ZR36057_FVAP_NAY) |
	      (zr->jpg_settings.img_height << ZR36057_FVAP_PAY);
	btwrite(reg, ZR36057_FVAP);

	/* horizontal */
	if (zr->card.vfe_pol.hsync_pol)
		btor(ZR36057_VFEHCR_HSPol, ZR36057_VFEHCR);
	else
		btand(~ZR36057_VFEHCR_HSPol, ZR36057_VFEHCR);
	reg = ((tvn->HSyncStart) << ZR36057_HSP_HsyncStart) |
	      (tvn->Wt << ZR36057_HSP_LineTot);
	btwrite(reg, ZR36057_HSP);
	reg = ((zr->jpg_settings.img_x +
		tvn->HStart + 4) << ZR36057_FHAP_NAX) |
	      (zr->jpg_settings.img_width << ZR36057_FHAP_PAX);
	btwrite(reg, ZR36057_FHAP);

	/* field process parameters */
	if (zr->jpg_settings.odd_even)
		reg = ZR36057_FPP_Odd_Even;
	else
		reg = 0;

	btwrite(reg, ZR36057_FPP);

	/* Set proper VCLK Polarity, else colors will be wrong during playback */
	//btor(ZR36057_VFESPFR_VCLKPol, ZR36057_VFESPFR);

	/* code base address */
	reg = virt_to_bus(zr->stat_com);
	btwrite(reg, ZR36057_JCBA);

	/* FIFO threshold (FIFO is 160. double words) */
	/* NOTE: decimal values here */
	switch (mode) {

	case BUZ_MODE_STILL_COMPRESS:
	case BUZ_MODE_MOTION_COMPRESS:
		if (zr->card.type != BUZ)
			reg = 140;
		else
			reg = 60;
		break;

	case BUZ_MODE_STILL_DECOMPRESS:
	case BUZ_MODE_MOTION_DECOMPRESS:
		reg = 20;
		break;

	default:
		reg = 80;
		break;

	}
	btwrite(reg, ZR36057_JCFT);
	zr36057_adjust_vfe(zr, mode);

}