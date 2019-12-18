#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct cx23885_tsport {int gen_ctrl_val; int ts_clk_en_val; int vld_misc_val; int hw_sop_ctrl_val; void* src_sel_val; } ;
struct cx23885_dev {int board; TYPE_2__* sd_cx25840; TYPE_1__* i2c_bus; int /*<<< orphan*/  v4l2_dev; struct cx23885_tsport ts2; struct cx23885_tsport ts1; } ;
typedef  int /*<<< orphan*/  eeprom ;
struct TYPE_7__ {int addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  grp_id; } ;
struct TYPE_5__ {scalar_t__ i2c_rc; int /*<<< orphan*/  i2c_adap; TYPE_4__ i2c_client; } ;

/* Variables and functions */
#define  CX23885_BOARD_COMPRO_VIDEOMATE_E650F 156 
#define  CX23885_BOARD_COMPRO_VIDEOMATE_E800 155 
#define  CX23885_BOARD_DVBWORLD_2005 154 
#define  CX23885_BOARD_DVICO_FUSIONHDTV_5_EXP 153 
#define  CX23885_BOARD_DVICO_FUSIONHDTV_7_DUAL_EXP 152 
#define  CX23885_BOARD_DVICO_FUSIONHDTV_DVB_T_DUAL_EXP 151 
#define  CX23885_BOARD_GOTVIEW_X5_3D_HYBRID 150 
#define  CX23885_BOARD_HAUPPAUGE_HVR1200 149 
#define  CX23885_BOARD_HAUPPAUGE_HVR1210 148 
#define  CX23885_BOARD_HAUPPAUGE_HVR1250 147 
#define  CX23885_BOARD_HAUPPAUGE_HVR1255 146 
#define  CX23885_BOARD_HAUPPAUGE_HVR1270 145 
#define  CX23885_BOARD_HAUPPAUGE_HVR1275 144 
#define  CX23885_BOARD_HAUPPAUGE_HVR1290 143 
#define  CX23885_BOARD_HAUPPAUGE_HVR1400 142 
#define  CX23885_BOARD_HAUPPAUGE_HVR1500 141 
#define  CX23885_BOARD_HAUPPAUGE_HVR1500Q 140 
#define  CX23885_BOARD_HAUPPAUGE_HVR1700 139 
#define  CX23885_BOARD_HAUPPAUGE_HVR1800 138 
#define  CX23885_BOARD_HAUPPAUGE_HVR1800lp 137 
#define  CX23885_BOARD_HAUPPAUGE_HVR1850 136 
#define  CX23885_BOARD_LEADTEK_WINFAST_PXDVR3200_H 135 
#define  CX23885_BOARD_LEADTEK_WINFAST_PXTV1200 134 
#define  CX23885_BOARD_MAGICPRO_PROHDTVE2 133 
#define  CX23885_BOARD_MYGICA_X8506 132 
#define  CX23885_BOARD_MYGICA_X8558PRO 131 
#define  CX23885_BOARD_NETUP_DUAL_DVBS2_CI 130 
#define  CX23885_BOARD_TBS_6920 129 
#define  CX23885_BOARD_TEVII_S470 128 
 int /*<<< orphan*/  CX23885_HW_AV_CORE ; 
 void* CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  enable_885_ir ; 
 int /*<<< orphan*/  hauppauge_eeprom (struct cx23885_dev*,int*) ; 
 int /*<<< orphan*/  load_fw ; 
 int /*<<< orphan*/  netup_initialize (struct cx23885_dev*) ; 
 int /*<<< orphan*/  tveeprom_read (TYPE_4__*,int*,int) ; 
 TYPE_2__* v4l2_i2c_new_subdev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_subdev_call (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cx23885_card_setup(struct cx23885_dev *dev)
{
	struct cx23885_tsport *ts1 = &dev->ts1;
	struct cx23885_tsport *ts2 = &dev->ts2;

	static u8 eeprom[256];

	if (dev->i2c_bus[0].i2c_rc == 0) {
		dev->i2c_bus[0].i2c_client.addr = 0xa0 >> 1;
		tveeprom_read(&dev->i2c_bus[0].i2c_client,
			      eeprom, sizeof(eeprom));
	}

	switch (dev->board) {
	case CX23885_BOARD_HAUPPAUGE_HVR1250:
		if (dev->i2c_bus[0].i2c_rc == 0) {
			if (eeprom[0x80] != 0x84)
				hauppauge_eeprom(dev, eeprom+0xc0);
			else
				hauppauge_eeprom(dev, eeprom+0x80);
		}
		break;
	case CX23885_BOARD_HAUPPAUGE_HVR1500:
	case CX23885_BOARD_HAUPPAUGE_HVR1500Q:
	case CX23885_BOARD_HAUPPAUGE_HVR1400:
		if (dev->i2c_bus[0].i2c_rc == 0)
			hauppauge_eeprom(dev, eeprom+0x80);
		break;
	case CX23885_BOARD_HAUPPAUGE_HVR1800:
	case CX23885_BOARD_HAUPPAUGE_HVR1800lp:
	case CX23885_BOARD_HAUPPAUGE_HVR1200:
	case CX23885_BOARD_HAUPPAUGE_HVR1700:
	case CX23885_BOARD_HAUPPAUGE_HVR1270:
	case CX23885_BOARD_HAUPPAUGE_HVR1275:
	case CX23885_BOARD_HAUPPAUGE_HVR1255:
	case CX23885_BOARD_HAUPPAUGE_HVR1210:
	case CX23885_BOARD_HAUPPAUGE_HVR1850:
	case CX23885_BOARD_HAUPPAUGE_HVR1290:
		if (dev->i2c_bus[0].i2c_rc == 0)
			hauppauge_eeprom(dev, eeprom+0xc0);
		break;
	}

	switch (dev->board) {
	case CX23885_BOARD_DVICO_FUSIONHDTV_7_DUAL_EXP:
	case CX23885_BOARD_DVICO_FUSIONHDTV_DVB_T_DUAL_EXP:
		ts2->gen_ctrl_val  = 0xc; /* Serial bus + punctured clock */
		ts2->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts2->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		/* break omitted intentionally */
	case CX23885_BOARD_DVICO_FUSIONHDTV_5_EXP:
		ts1->gen_ctrl_val  = 0xc; /* Serial bus + punctured clock */
		ts1->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts1->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		break;
	case CX23885_BOARD_HAUPPAUGE_HVR1800:
		/* Defaults for VID B - Analog encoder */
		/* DREQ_POL, SMODE, PUNC_CLK, MCLK_POL Serial bus + punc clk */
		ts1->gen_ctrl_val    = 0x10e;
		ts1->ts_clk_en_val   = 0x1; /* Enable TS_CLK */
		ts1->src_sel_val     = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;

		/* APB_TSVALERR_POL (active low)*/
		ts1->vld_misc_val    = 0x2000;
		ts1->hw_sop_ctrl_val = (0x47 << 16 | 188 << 4 | 0xc);

		/* Defaults for VID C */
		ts2->gen_ctrl_val  = 0xc; /* Serial bus + punctured clock */
		ts2->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts2->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		break;
	case CX23885_BOARD_TBS_6920:
		ts1->gen_ctrl_val  = 0x4; /* Parallel */
		ts1->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts1->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		break;
	case CX23885_BOARD_TEVII_S470:
	case CX23885_BOARD_DVBWORLD_2005:
		ts1->gen_ctrl_val  = 0x5; /* Parallel */
		ts1->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts1->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		break;
	case CX23885_BOARD_NETUP_DUAL_DVBS2_CI:
		ts1->gen_ctrl_val  = 0xc; /* Serial bus + punctured clock */
		ts1->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts1->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		ts2->gen_ctrl_val  = 0xc; /* Serial bus + punctured clock */
		ts2->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts2->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		break;
	case CX23885_BOARD_MYGICA_X8506:
	case CX23885_BOARD_MAGICPRO_PROHDTVE2:
		ts1->gen_ctrl_val  = 0x5; /* Parallel */
		ts1->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts1->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		break;
	case CX23885_BOARD_MYGICA_X8558PRO:
		ts1->gen_ctrl_val  = 0x5; /* Parallel */
		ts1->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts1->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		ts2->gen_ctrl_val  = 0xc; /* Serial bus + punctured clock */
		ts2->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts2->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		break;
	case CX23885_BOARD_HAUPPAUGE_HVR1250:
	case CX23885_BOARD_HAUPPAUGE_HVR1500:
	case CX23885_BOARD_HAUPPAUGE_HVR1500Q:
	case CX23885_BOARD_HAUPPAUGE_HVR1800lp:
	case CX23885_BOARD_HAUPPAUGE_HVR1200:
	case CX23885_BOARD_HAUPPAUGE_HVR1700:
	case CX23885_BOARD_HAUPPAUGE_HVR1400:
	case CX23885_BOARD_LEADTEK_WINFAST_PXDVR3200_H:
	case CX23885_BOARD_COMPRO_VIDEOMATE_E650F:
	case CX23885_BOARD_HAUPPAUGE_HVR1270:
	case CX23885_BOARD_HAUPPAUGE_HVR1275:
	case CX23885_BOARD_HAUPPAUGE_HVR1255:
	case CX23885_BOARD_HAUPPAUGE_HVR1210:
	case CX23885_BOARD_HAUPPAUGE_HVR1850:
	case CX23885_BOARD_COMPRO_VIDEOMATE_E800:
	case CX23885_BOARD_HAUPPAUGE_HVR1290:
	case CX23885_BOARD_GOTVIEW_X5_3D_HYBRID:
	default:
		ts2->gen_ctrl_val  = 0xc; /* Serial bus + punctured clock */
		ts2->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts2->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
	}

	/* Certain boards support analog, or require the avcore to be
	 * loaded, ensure this happens.
	 */
	switch (dev->board) {
	case CX23885_BOARD_TEVII_S470:
	case CX23885_BOARD_HAUPPAUGE_HVR1250:
		/* Currently only enabled for the integrated IR controller */
		if (!enable_885_ir)
			break;
	case CX23885_BOARD_HAUPPAUGE_HVR1800:
	case CX23885_BOARD_HAUPPAUGE_HVR1800lp:
	case CX23885_BOARD_HAUPPAUGE_HVR1700:
	case CX23885_BOARD_LEADTEK_WINFAST_PXDVR3200_H:
	case CX23885_BOARD_COMPRO_VIDEOMATE_E650F:
	case CX23885_BOARD_NETUP_DUAL_DVBS2_CI:
	case CX23885_BOARD_COMPRO_VIDEOMATE_E800:
	case CX23885_BOARD_HAUPPAUGE_HVR1850:
	case CX23885_BOARD_MYGICA_X8506:
	case CX23885_BOARD_MAGICPRO_PROHDTVE2:
	case CX23885_BOARD_HAUPPAUGE_HVR1290:
	case CX23885_BOARD_LEADTEK_WINFAST_PXTV1200:
	case CX23885_BOARD_GOTVIEW_X5_3D_HYBRID:
		dev->sd_cx25840 = v4l2_i2c_new_subdev(&dev->v4l2_dev,
				&dev->i2c_bus[2].i2c_adap,
				"cx25840", 0x88 >> 1, NULL);
		if (dev->sd_cx25840) {
			dev->sd_cx25840->grp_id = CX23885_HW_AV_CORE;
			v4l2_subdev_call(dev->sd_cx25840, core, load_fw);
		}
		break;
	}

	/* AUX-PLL 27MHz CLK */
	switch (dev->board) {
	case CX23885_BOARD_NETUP_DUAL_DVBS2_CI:
		netup_initialize(dev);
		break;
	}
}