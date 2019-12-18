#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct atmel_abdac {int rates_num; int /*<<< orphan*/  constraints_rates; int /*<<< orphan*/ * rates; struct snd_pcm_substream* substream; } ;
struct TYPE_4__ {int /*<<< orphan*/  rate_min; int /*<<< orphan*/  rate_max; } ;
struct TYPE_3__ {TYPE_2__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 TYPE_2__ atmel_abdac_hw ; 
 int snd_pcm_hw_constraint_list (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct atmel_abdac* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int atmel_abdac_open(struct snd_pcm_substream *substream)
{
	struct atmel_abdac *dac = snd_pcm_substream_chip(substream);

	dac->substream = substream;
	atmel_abdac_hw.rate_max = dac->rates[dac->rates_num - 1];
	atmel_abdac_hw.rate_min = dac->rates[0];
	substream->runtime->hw = atmel_abdac_hw;

	return snd_pcm_hw_constraint_list(substream->runtime, 0,
			SNDRV_PCM_HW_PARAM_RATE, &dac->constraints_rates);
}