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
struct snd_pmac {int /*<<< orphan*/  capture; } ;
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 struct snd_pmac* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pmac_capture ; 
 int snd_pmac_pcm_open (struct snd_pmac*,int /*<<< orphan*/ *,struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_pmac_capture_open(struct snd_pcm_substream *subs)
{
	struct snd_pmac *chip = snd_pcm_substream_chip(subs);

	subs->runtime->hw = snd_pmac_capture;
	return snd_pmac_pcm_open(chip, &chip->capture, subs);
}