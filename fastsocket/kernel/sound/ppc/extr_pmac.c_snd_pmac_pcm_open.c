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
struct snd_pmac {int num_freqs; int freqs_ok; int /*<<< orphan*/  can_duplex; scalar_t__ can_capture; int /*<<< orphan*/  formats_ok; int /*<<< orphan*/ * freq_table; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct TYPE_3__ {scalar_t__ periods_max; int /*<<< orphan*/  info; int /*<<< orphan*/  formats; int /*<<< orphan*/  rate_min; int /*<<< orphan*/  rate_max; int /*<<< orphan*/  rates; } ;
struct snd_pcm_runtime {TYPE_1__ hw; struct pmac_stream* private_data; } ;
struct TYPE_4__ {scalar_t__ size; } ;
struct pmac_stream {TYPE_2__ cmd; int /*<<< orphan*/  stream; struct snd_pcm_substream* substream; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_FORMAT ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIODS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  SNDRV_PCM_INFO_HALF_DUPLEX ; 
 int /*<<< orphan*/  SNDRV_PCM_INFO_JOINT_DUPLEX ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_integer (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_hw_rule_add (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_pmac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_pcm_rate_to_rate_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pmac_hw_rule_format ; 
 int /*<<< orphan*/  snd_pmac_hw_rule_rate ; 

__attribute__((used)) static int snd_pmac_pcm_open(struct snd_pmac *chip, struct pmac_stream *rec,
			     struct snd_pcm_substream *subs)
{
	struct snd_pcm_runtime *runtime = subs->runtime;
	int i;

	/* look up frequency table and fill bit mask */
	runtime->hw.rates = 0;
	for (i = 0; i < chip->num_freqs; i++)
		if (chip->freqs_ok & (1 << i))
			runtime->hw.rates |=
				snd_pcm_rate_to_rate_bit(chip->freq_table[i]);

	/* check for minimum and maximum rates */
	for (i = 0; i < chip->num_freqs; i++) {
		if (chip->freqs_ok & (1 << i)) {
			runtime->hw.rate_max = chip->freq_table[i];
			break;
		}
	}
	for (i = chip->num_freqs - 1; i >= 0; i--) {
		if (chip->freqs_ok & (1 << i)) {
			runtime->hw.rate_min = chip->freq_table[i];
			break;
		}
	}
	runtime->hw.formats = chip->formats_ok;
	if (chip->can_capture) {
		if (! chip->can_duplex)
			runtime->hw.info |= SNDRV_PCM_INFO_HALF_DUPLEX;
		runtime->hw.info |= SNDRV_PCM_INFO_JOINT_DUPLEX;
	}
	runtime->private_data = rec;
	rec->substream = subs;

#if 0 /* FIXME: still under development.. */
	snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_RATE,
			    snd_pmac_hw_rule_rate, chip, rec->stream, -1);
	snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_FORMAT,
			    snd_pmac_hw_rule_format, chip, rec->stream, -1);
#endif

	runtime->hw.periods_max = rec->cmd.size - 1;

	/* constraints to fix choppy sound */
	snd_pcm_hw_constraint_integer(runtime, SNDRV_PCM_HW_PARAM_PERIODS);
	return 0;
}