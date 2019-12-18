#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  unsigned int u32 ;
struct TYPE_7__ {unsigned int hpitch; scalar_t__ storage_mode; } ;
struct TYPE_6__ {unsigned int data_sz; } ;
struct TYPE_5__ {scalar_t__ hd_pol; scalar_t__ vd_pol; scalar_t__ fid_pol; } ;
struct vpif_channel_config_params {scalar_t__ capture_format; scalar_t__ ycmux_mode; scalar_t__ frm_fmt; } ;
struct vpif_params {TYPE_3__ video_params; TYPE_2__ params; TYPE_1__ iface; struct vpif_channel_config_params std_info; } ;
struct TYPE_8__ {unsigned int ch_ctrl; unsigned int line_offset; } ;

/* Variables and functions */
 unsigned int VPIF_CAPTURE_CH_NIP ; 
 unsigned int VPIF_CH_DATA_MODE_BIT ; 
 unsigned int VPIF_CH_DATA_WIDTH_BIT ; 
 unsigned int VPIF_CH_FID_POLARITY_BIT ; 
 unsigned int VPIF_CH_H_VALID_POLARITY_BIT ; 
 unsigned int VPIF_CH_INPUT_FIELD_FRAME_BIT ; 
 int /*<<< orphan*/  VPIF_CH_SDR_FMT_BIT ; 
 unsigned int VPIF_CH_V_VALID_POLARITY_BIT ; 
 unsigned int VPIF_CH_YC_MUX_BIT ; 
 unsigned int VPIF_DISPLAY_CH_NIP ; 
 int /*<<< orphan*/  VPIF_DISPLAY_PIX_EN_BIT ; 
 unsigned int regr (unsigned int) ; 
 int /*<<< orphan*/  regw (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  vpif_clr_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpif_set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpif_wr_bit (unsigned int,unsigned int,scalar_t__) ; 
 TYPE_4__* vpifregs ; 

__attribute__((used)) static void config_vpif_params(struct vpif_params *vpifparams,
				u8 channel_id, u8 found)
{
	const struct vpif_channel_config_params *config = &vpifparams->std_info;
	u32 value, ch_nip, reg;
	u8 start, end;
	int i;

	start = channel_id;
	end = channel_id + found;

	for (i = start; i < end; i++) {
		reg = vpifregs[i].ch_ctrl;
		if (channel_id < 2)
			ch_nip = VPIF_CAPTURE_CH_NIP;
		else
			ch_nip = VPIF_DISPLAY_CH_NIP;

		vpif_wr_bit(reg, ch_nip, config->frm_fmt);
		vpif_wr_bit(reg, VPIF_CH_YC_MUX_BIT, config->ycmux_mode);
		vpif_wr_bit(reg, VPIF_CH_INPUT_FIELD_FRAME_BIT,
					vpifparams->video_params.storage_mode);

		/* Set raster scanning SDR Format */
		vpif_clr_bit(reg, VPIF_CH_SDR_FMT_BIT);
		vpif_wr_bit(reg, VPIF_CH_DATA_MODE_BIT, config->capture_format);

		if (channel_id > 1)	/* Set the Pixel enable bit */
			vpif_set_bit(reg, VPIF_DISPLAY_PIX_EN_BIT);
		else if (config->capture_format) {
			/* Set the polarity of various pins */
			vpif_wr_bit(reg, VPIF_CH_FID_POLARITY_BIT,
					vpifparams->iface.fid_pol);
			vpif_wr_bit(reg, VPIF_CH_V_VALID_POLARITY_BIT,
					vpifparams->iface.vd_pol);
			vpif_wr_bit(reg, VPIF_CH_H_VALID_POLARITY_BIT,
					vpifparams->iface.hd_pol);

			value = regr(reg);
			/* Set data width */
			value &= ((~(unsigned int)(0x3)) <<
					VPIF_CH_DATA_WIDTH_BIT);
			value |= ((vpifparams->params.data_sz) <<
						     VPIF_CH_DATA_WIDTH_BIT);
			regw(value, reg);
		}

		/* Write the pitch in the driver */
		regw((vpifparams->video_params.hpitch),
						vpifregs[i].line_offset);
	}
}