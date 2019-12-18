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
struct TYPE_5__ {struct ssp_device* ssp; } ;
struct ssp_priv {int dai_fmt; TYPE_2__ dev; } ;
struct ssp_device {TYPE_3__* pdev; } ;
struct snd_soc_pcm_runtime {TYPE_1__* dai; } ;
struct snd_soc_dai {scalar_t__ dma_data; struct ssp_priv* private_data; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {struct snd_soc_dai* cpu_dai; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_FORMAT_S16_LE 131 
#define  SNDRV_PCM_FORMAT_S24_LE 130 
#define  SNDRV_PCM_FORMAT_S32_LE 129 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 128 
 int /*<<< orphan*/  SSCR0 ; 
 int SSCR0_DSS ; 
 int SSCR0_DataSize (int) ; 
 int SSCR0_EDSS ; 
 int SSCR0_FPCKE ; 
 int SSCR0_MOD ; 
 int SSCR0_SSE ; 
 int /*<<< orphan*/  SSPSP ; 
 int SSPSP_DMYSTOP (int) ; 
 int SSPSP_DMYSTRT (int) ; 
 int SSPSP_EDMYSTOP (int) ; 
 int SSPSP_SFRMDLY (int) ; 
 int SSPSP_SFRMWDTH (int) ; 
 int /*<<< orphan*/  SSTSA ; 
 int /*<<< orphan*/  cpu_is_pxa3xx () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dump_registers (struct ssp_device*) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int params_format (struct snd_pcm_hw_params*) ; 
 int snd_pcm_format_physical_width (int) ; 
 scalar_t__ ssp_get_dma_params (struct ssp_device*,int,int) ; 
 int ssp_get_scr (struct ssp_device*) ; 
 int ssp_read_reg (struct ssp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssp_write_reg (struct ssp_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pxa_ssp_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params,
				struct snd_soc_dai *dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *cpu_dai = rtd->dai->cpu_dai;
	struct ssp_priv *priv = cpu_dai->private_data;
	struct ssp_device *ssp = priv->dev.ssp;
	int chn = params_channels(params);
	u32 sscr0;
	u32 sspsp;
	int width = snd_pcm_format_physical_width(params_format(params));
	int ttsa = ssp_read_reg(ssp, SSTSA) & 0xf;

	/* generate correct DMA params */
	if (cpu_dai->dma_data)
		kfree(cpu_dai->dma_data);

	/* Network mode with one active slot (ttsa == 1) can be used
	 * to force 16-bit frame width on the wire (for S16_LE), even
	 * with two channels. Use 16-bit DMA transfers for this case.
	 */
	cpu_dai->dma_data = ssp_get_dma_params(ssp,
			((chn == 2) && (ttsa != 1)) || (width == 32),
			substream->stream == SNDRV_PCM_STREAM_PLAYBACK);

	/* we can only change the settings if the port is not in use */
	if (ssp_read_reg(ssp, SSCR0) & SSCR0_SSE)
		return 0;

	/* clear selected SSP bits */
	sscr0 = ssp_read_reg(ssp, SSCR0) & ~(SSCR0_DSS | SSCR0_EDSS);
	ssp_write_reg(ssp, SSCR0, sscr0);

	/* bit size */
	sscr0 = ssp_read_reg(ssp, SSCR0);
	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S16_LE:
#ifdef CONFIG_PXA3xx
		if (cpu_is_pxa3xx())
			sscr0 |= SSCR0_FPCKE;
#endif
		sscr0 |= SSCR0_DataSize(16);
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
		sscr0 |= (SSCR0_EDSS | SSCR0_DataSize(8));
		break;
	case SNDRV_PCM_FORMAT_S32_LE:
		sscr0 |= (SSCR0_EDSS | SSCR0_DataSize(16));
		break;
	}
	ssp_write_reg(ssp, SSCR0, sscr0);

	switch (priv->dai_fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
	       sspsp = ssp_read_reg(ssp, SSPSP);

		if ((ssp_get_scr(ssp) == 4) && (width == 16)) {
			/* This is a special case where the bitclk is 64fs
			* and we're not dealing with 2*32 bits of audio
			* samples.
			*
			* The SSP values used for that are all found out by
			* trying and failing a lot; some of the registers
			* needed for that mode are only available on PXA3xx.
			*/

#ifdef CONFIG_PXA3xx
			if (!cpu_is_pxa3xx())
				return -EINVAL;

			sspsp |= SSPSP_SFRMWDTH(width * 2);
			sspsp |= SSPSP_SFRMDLY(width * 4);
			sspsp |= SSPSP_EDMYSTOP(3);
			sspsp |= SSPSP_DMYSTOP(3);
			sspsp |= SSPSP_DMYSTRT(1);
#else
			return -EINVAL;
#endif
		} else {
			/* The frame width is the width the LRCLK is
			 * asserted for; the delay is expressed in
			 * half cycle units.  We need the extra cycle
			 * because the data starts clocking out one BCLK
			 * after LRCLK changes polarity.
			 */
			sspsp |= SSPSP_SFRMWDTH(width + 1);
			sspsp |= SSPSP_SFRMDLY((width + 1) * 2);
			sspsp |= SSPSP_DMYSTRT(1);
		}

		ssp_write_reg(ssp, SSPSP, sspsp);
		break;
	default:
		break;
	}

	/* When we use a network mode, we always require TDM slots
	 * - complain loudly and fail if they've not been set up yet.
	 */
	if ((sscr0 & SSCR0_MOD) && !ttsa) {
		dev_err(&ssp->pdev->dev, "No TDM timeslot configured\n");
		return -EINVAL;
	}

	dump_registers(ssp);

	return 0;
}