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
struct snd_pcm_substream {int f_flags; TYPE_1__* pcm; } ;
struct snd_card {int dummy; } ;
struct file {int f_flags; } ;
struct TYPE_2__ {struct snd_card* card; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_POWER_D0 ; 
 int snd_pcm_action_nonatomic (int /*<<< orphan*/ *,struct snd_pcm_substream*,int) ; 
 int /*<<< orphan*/  snd_pcm_action_prepare ; 
 int /*<<< orphan*/  snd_power_lock (struct snd_card*) ; 
 int /*<<< orphan*/  snd_power_unlock (struct snd_card*) ; 
 int snd_power_wait (struct snd_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_pcm_prepare(struct snd_pcm_substream *substream,
			   struct file *file)
{
	int res;
	struct snd_card *card = substream->pcm->card;
	int f_flags;

	if (file)
		f_flags = file->f_flags;
	else
		f_flags = substream->f_flags;

	snd_power_lock(card);
	if ((res = snd_power_wait(card, SNDRV_CTL_POWER_D0)) >= 0)
		res = snd_pcm_action_nonatomic(&snd_pcm_action_prepare,
					       substream, f_flags);
	snd_power_unlock(card);
	return res;
}