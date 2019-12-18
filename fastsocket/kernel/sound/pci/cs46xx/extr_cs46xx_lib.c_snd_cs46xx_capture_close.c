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
struct snd_pcm_substream {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw_buf; int /*<<< orphan*/ * substream; } ;
struct snd_cs46xx {int /*<<< orphan*/  (* active_ctrl ) (struct snd_cs46xx*,int) ;TYPE_1__ capt; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_dma_free_pages (int /*<<< orphan*/ *) ; 
 struct snd_cs46xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  stub1 (struct snd_cs46xx*,int) ; 

__attribute__((used)) static int snd_cs46xx_capture_close(struct snd_pcm_substream *substream)
{
	struct snd_cs46xx *chip = snd_pcm_substream_chip(substream);

	chip->capt.substream = NULL;
	snd_dma_free_pages(&chip->capt.hw_buf);
	chip->active_ctrl(chip, -1);

	return 0;
}