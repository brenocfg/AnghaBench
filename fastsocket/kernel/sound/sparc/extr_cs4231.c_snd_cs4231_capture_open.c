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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  dma_bytes; int /*<<< orphan*/  dma_area; int /*<<< orphan*/  hw; } ;
struct snd_cs4231 {scalar_t__ c_periods_sent; struct snd_pcm_substream* capture_substream; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS4231_MODE_RECORD ; 
 int /*<<< orphan*/  snd_cs4231_capture ; 
 int snd_cs4231_open (struct snd_cs4231*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cs4231_xrate (struct snd_pcm_runtime*) ; 
 int /*<<< orphan*/  snd_free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_set_sync (struct snd_pcm_substream*) ; 
 struct snd_cs4231* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_cs4231_capture_open(struct snd_pcm_substream *substream)
{
	struct snd_cs4231 *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	int err;

	runtime->hw = snd_cs4231_capture;

	err = snd_cs4231_open(chip, CS4231_MODE_RECORD);
	if (err < 0) {
		snd_free_pages(runtime->dma_area, runtime->dma_bytes);
		return err;
	}
	chip->capture_substream = substream;
	chip->c_periods_sent = 0;
	snd_pcm_set_sync(substream);
	snd_cs4231_xrate(runtime);

	return 0;
}