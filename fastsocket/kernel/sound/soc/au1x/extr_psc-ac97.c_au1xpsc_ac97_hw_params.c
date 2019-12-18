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
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {scalar_t__ msbits; } ;
struct au1xpsc_audio_data {scalar_t__ rate; unsigned long cfg; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_CFG (struct au1xpsc_audio_data*) ; 
 int /*<<< orphan*/  AC97_STAT (struct au1xpsc_audio_data*) ; 
 int EINVAL ; 
 int PCM_TX ; 
 unsigned long PSC_AC97CFG_DE_ENABLE ; 
 scalar_t__ PSC_AC97CFG_GET_LEN (unsigned long) ; 
 unsigned long PSC_AC97CFG_LEN_MASK ; 
 unsigned long PSC_AC97CFG_RXSLOT_ENA (int) ; 
 unsigned long PSC_AC97CFG_RXSLOT_MASK ; 
 unsigned long PSC_AC97CFG_SET_LEN (scalar_t__) ; 
 unsigned long PSC_AC97CFG_TXSLOT_ENA (int) ; 
 unsigned long PSC_AC97CFG_TXSLOT_MASK ; 
 int PSC_AC97STAT_DR ; 
 unsigned long PSC_AC97STAT_RB ; 
 unsigned long PSC_AC97STAT_TB ; 
 int SUBSTREAM_TYPE (struct snd_pcm_substream*) ; 
 struct au1xpsc_audio_data* au1xpsc_ac97_workdata ; 
 int au_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au_sync () ; 
 int /*<<< orphan*/  au_writel (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 scalar_t__ params_rate (struct snd_pcm_hw_params*) ; 

__attribute__((used)) static int au1xpsc_ac97_hw_params(struct snd_pcm_substream *substream,
				  struct snd_pcm_hw_params *params,
				  struct snd_soc_dai *dai)
{
	/* FIXME */
	struct au1xpsc_audio_data *pscdata = au1xpsc_ac97_workdata;
	unsigned long r, ro, stat;
	int chans, stype = SUBSTREAM_TYPE(substream);

	chans = params_channels(params);

	r = ro = au_readl(AC97_CFG(pscdata));
	stat = au_readl(AC97_STAT(pscdata));

	/* already active? */
	if (stat & (PSC_AC97STAT_TB | PSC_AC97STAT_RB)) {
		/* reject parameters not currently set up */
		if ((PSC_AC97CFG_GET_LEN(r) != params->msbits) ||
		    (pscdata->rate != params_rate(params)))
			return -EINVAL;
	} else {

		/* set sample bitdepth: REG[24:21]=(BITS-2)/2 */
		r &= ~PSC_AC97CFG_LEN_MASK;
		r |= PSC_AC97CFG_SET_LEN(params->msbits);

		/* channels: enable slots for front L/R channel */
		if (stype == PCM_TX) {
			r &= ~PSC_AC97CFG_TXSLOT_MASK;
			r |= PSC_AC97CFG_TXSLOT_ENA(3);
			r |= PSC_AC97CFG_TXSLOT_ENA(4);
		} else {
			r &= ~PSC_AC97CFG_RXSLOT_MASK;
			r |= PSC_AC97CFG_RXSLOT_ENA(3);
			r |= PSC_AC97CFG_RXSLOT_ENA(4);
		}

		/* do we need to poke the hardware? */
		if (!(r ^ ro))
			goto out;

		/* ac97 engine is about to be disabled */
		mutex_lock(&pscdata->lock);

		/* disable AC97 device controller first... */
		au_writel(r & ~PSC_AC97CFG_DE_ENABLE, AC97_CFG(pscdata));
		au_sync();

		/* ...wait for it... */
		while (au_readl(AC97_STAT(pscdata)) & PSC_AC97STAT_DR)
			asm volatile ("nop");

		/* ...write config... */
		au_writel(r, AC97_CFG(pscdata));
		au_sync();

		/* ...enable the AC97 controller again... */
		au_writel(r | PSC_AC97CFG_DE_ENABLE, AC97_CFG(pscdata));
		au_sync();

		/* ...and wait for ready bit */
		while (!(au_readl(AC97_STAT(pscdata)) & PSC_AC97STAT_DR))
			asm volatile ("nop");

		mutex_unlock(&pscdata->lock);

		pscdata->cfg = r;
		pscdata->rate = params_rate(params);
	}

out:
	return 0;
}