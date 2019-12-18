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
struct snd_pcm_substream {size_t stream; } ;
struct hda_pcm_stream {int dummy; } ;
struct azx_pcm {int /*<<< orphan*/  codec; struct hda_pcm_stream** hinfo; struct azx* chip; } ;
struct azx_dev {scalar_t__ prepared; scalar_t__ format_val; scalar_t__ period_bytes; scalar_t__ bufsize; } ;
struct azx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SD_BDLPL ; 
 int /*<<< orphan*/  SD_BDLPU ; 
 int /*<<< orphan*/  SD_CTL ; 
 int /*<<< orphan*/  azx_sd_writel (struct azx_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsp_is_locked (struct azx_dev*) ; 
 int /*<<< orphan*/  dsp_lock (struct azx_dev*) ; 
 int /*<<< orphan*/  dsp_unlock (struct azx_dev*) ; 
 struct azx_dev* get_azx_dev (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  mark_runtime_wc (struct azx*,struct azx_dev*,struct snd_pcm_substream*,int) ; 
 int /*<<< orphan*/  snd_hda_codec_cleanup (int /*<<< orphan*/ ,struct hda_pcm_stream*,struct snd_pcm_substream*) ; 
 int snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 
 struct azx_pcm* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int azx_pcm_hw_free(struct snd_pcm_substream *substream)
{
	struct azx_pcm *apcm = snd_pcm_substream_chip(substream);
	struct azx_dev *azx_dev = get_azx_dev(substream);
	struct azx *chip = apcm->chip;
	struct hda_pcm_stream *hinfo = apcm->hinfo[substream->stream];

	/* reset BDL address */
	dsp_lock(azx_dev);
	if (!dsp_is_locked(azx_dev)) {
		azx_sd_writel(azx_dev, SD_BDLPL, 0);
		azx_sd_writel(azx_dev, SD_BDLPU, 0);
		azx_sd_writel(azx_dev, SD_CTL, 0);
		azx_dev->bufsize = 0;
		azx_dev->period_bytes = 0;
		azx_dev->format_val = 0;
	}

	snd_hda_codec_cleanup(apcm->codec, hinfo, substream);

	mark_runtime_wc(chip, azx_dev, substream, false);
	azx_dev->prepared = 0;
	dsp_unlock(azx_dev);
	return snd_pcm_lib_free_pages(substream);
}