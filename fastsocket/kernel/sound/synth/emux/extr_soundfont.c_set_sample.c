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
struct soundfont_voice_info {int /*<<< orphan*/  sample_mode; int /*<<< orphan*/  loopend; int /*<<< orphan*/  loopstart; int /*<<< orphan*/  end; int /*<<< orphan*/  start; int /*<<< orphan*/  sample; } ;
struct snd_soundfont {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mode_flags; scalar_t__ loopend; scalar_t__ loopstart; scalar_t__ end; scalar_t__ start; } ;
struct snd_sf_sample {TYPE_1__ v; } ;

/* Variables and functions */
 struct snd_sf_sample* find_sample (struct snd_soundfont*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct snd_sf_sample *
set_sample(struct snd_soundfont *sf, struct soundfont_voice_info *avp)
{
	struct snd_sf_sample *sample;

	sample = find_sample(sf, avp->sample);
	if (sample == NULL)
		return NULL;

	/* add in the actual sample offsets:
	 * The voice_info addresses define only the relative offset
	 * from sample pointers.  Here we calculate the actual DRAM
	 * offset from sample pointers.
	 */
	avp->start += sample->v.start;
	avp->end += sample->v.end;
	avp->loopstart += sample->v.loopstart;
	avp->loopend += sample->v.loopend;

	/* copy mode flags */
	avp->sample_mode = sample->v.mode_flags;

	return sample;
}