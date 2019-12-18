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
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_ali {int num_of_codecs; int /*<<< orphan*/ * ac97; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_LINE1_LEVEL ; 
 int /*<<< orphan*/  AC97_LINE1_RATE ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  snd_ac97_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_ali_hw_params (struct snd_pcm_substream*,struct snd_pcm_hw_params*) ; 
 struct snd_ali* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_ali_modem_hw_params(struct snd_pcm_substream *substream,
				 struct snd_pcm_hw_params *hw_params)
{
	struct snd_ali *chip = snd_pcm_substream_chip(substream);
	unsigned int modem_num = chip->num_of_codecs - 1;
	snd_ac97_write(chip->ac97[modem_num], AC97_LINE1_RATE,
		       params_rate(hw_params));
	snd_ac97_write(chip->ac97[modem_num], AC97_LINE1_LEVEL, 0);
	return snd_ali_hw_params(substream, hw_params);
}