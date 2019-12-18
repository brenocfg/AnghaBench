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
typedef  int u32 ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct fsi_priv {int chan; int fifo_max; int /*<<< orphan*/  dma_chan; } ;
struct TYPE_2__ {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  CKG1 ; 
 int CKG2 ; 
 int CR_FMT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CR_I2S ; 
 int /*<<< orphan*/  CR_MONO ; 
 int /*<<< orphan*/  CR_MONO_D ; 
 int /*<<< orphan*/  CR_PCM ; 
 int /*<<< orphan*/  CR_TDM ; 
 int /*<<< orphan*/  CR_TDM_D ; 
 int DI_FMT ; 
 int DO_FMT ; 
 int EINVAL ; 
#define  SH_FSI_BRM_INV 137 
#define  SH_FSI_BRS_INV 136 
#define  SH_FSI_FMT_I2S 135 
#define  SH_FSI_FMT_MONO 134 
#define  SH_FSI_FMT_MONO_DELAY 133 
#define  SH_FSI_FMT_PCM 132 
#define  SH_FSI_FMT_TDM 131 
#define  SH_FSI_FMT_TDM_DELAY 130 
 void* SH_FSI_GET_CH_I (int) ; 
 void* SH_FSI_GET_CH_O (int) ; 
 int SH_FSI_GET_IFMT (int) ; 
 int SH_FSI_GET_OFMT (int) ; 
 int SH_FSI_INVERSION_MASK ; 
#define  SH_FSI_LRM_INV 129 
#define  SH_FSI_LRS_INV 128 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fsi_clk_ctrl (struct fsi_priv*,int) ; 
 struct fsi_priv* fsi_get (struct snd_pcm_substream*) ; 
 int fsi_get_info_flags (struct fsi_priv*) ; 
 int /*<<< orphan*/  fsi_irq_init (struct fsi_priv*,int) ; 
 int fsi_is_master_mode (struct fsi_priv*,int) ; 
 int /*<<< orphan*/  fsi_reg_mask_set (struct fsi_priv*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  fsi_reg_write (struct fsi_priv*,int,int) ; 
 TYPE_1__* master ; 

__attribute__((used)) static int fsi_dai_startup(struct snd_pcm_substream *substream,
			   struct snd_soc_dai *dai)
{
	struct fsi_priv *fsi = fsi_get(substream);
	const char *msg;
	u32 flags = fsi_get_info_flags(fsi);
	u32 fmt;
	u32 reg;
	u32 data;
	int is_play = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK);
	int is_master;
	int ret = 0;

	clk_enable(master->clk);

	/* CKG1 */
	data = is_play ? (1 << 0) : (1 << 4);
	is_master = fsi_is_master_mode(fsi, is_play);
	if (is_master)
		fsi_reg_mask_set(fsi, CKG1, data, data);
	else
		fsi_reg_mask_set(fsi, CKG1, data, 0);

	/* clock inversion (CKG2) */
	data = 0;
	switch (SH_FSI_INVERSION_MASK & flags) {
	case SH_FSI_LRM_INV:
		data = 1 << 12;
		break;
	case SH_FSI_BRM_INV:
		data = 1 << 8;
		break;
	case SH_FSI_LRS_INV:
		data = 1 << 4;
		break;
	case SH_FSI_BRS_INV:
		data = 1 << 0;
		break;
	}
	fsi_reg_write(fsi, CKG2, data);

	/* do fmt, di fmt */
	data = 0;
	reg = is_play ? DO_FMT : DI_FMT;
	fmt = is_play ? SH_FSI_GET_OFMT(flags) : SH_FSI_GET_IFMT(flags);
	switch (fmt) {
	case SH_FSI_FMT_MONO:
		msg = "MONO";
		data = CR_FMT(CR_MONO);
		fsi->chan = 1;
		break;
	case SH_FSI_FMT_MONO_DELAY:
		msg = "MONO Delay";
		data = CR_FMT(CR_MONO_D);
		fsi->chan = 1;
		break;
	case SH_FSI_FMT_PCM:
		msg = "PCM";
		data = CR_FMT(CR_PCM);
		fsi->chan = 2;
		break;
	case SH_FSI_FMT_I2S:
		msg = "I2S";
		data = CR_FMT(CR_I2S);
		fsi->chan = 2;
		break;
	case SH_FSI_FMT_TDM:
		msg = "TDM";
		data = CR_FMT(CR_TDM) | (fsi->chan - 1);
		fsi->chan = is_play ?
			SH_FSI_GET_CH_O(flags) : SH_FSI_GET_CH_I(flags);
		break;
	case SH_FSI_FMT_TDM_DELAY:
		msg = "TDM Delay";
		data = CR_FMT(CR_TDM_D) | (fsi->chan - 1);
		fsi->chan = is_play ?
			SH_FSI_GET_CH_O(flags) : SH_FSI_GET_CH_I(flags);
		break;
	default:
		dev_err(dai->dev, "unknown format.\n");
		return -EINVAL;
	}

	switch (fsi->chan) {
	case 1:
		fsi->fifo_max = 256;
		break;
	case 2:
		fsi->fifo_max = 128;
		break;
	case 3:
	case 4:
		fsi->fifo_max = 64;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
		fsi->fifo_max = 32;
		break;
	default:
		dev_err(dai->dev, "channel size error.\n");
		return -EINVAL;
	}

	fsi_reg_write(fsi, reg, data);
	dev_dbg(dai->dev, "use %s format (%d channel) use %d DMAC\n",
		msg, fsi->chan, fsi->dma_chan);

	/*
	 * clear clk reset if master mode
	 */
	if (is_master)
		fsi_clk_ctrl(fsi, 1);

	/* irq setting */
	fsi_irq_init(fsi, is_play);

	return ret;
}