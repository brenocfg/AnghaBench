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
struct snd_korg1212 {size_t cardState; int /*<<< orphan*/  lock; int /*<<< orphan*/  running; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  K1212_DEBUG_PRINTK (char*,int /*<<< orphan*/ ,int) ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int snd_korg1212_StopPlay (struct snd_korg1212*) ; 
 int snd_korg1212_TriggerPlay (struct snd_korg1212*) ; 
 struct snd_korg1212* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stateName ; 

__attribute__((used)) static int snd_korg1212_trigger(struct snd_pcm_substream *substream,
                           int cmd)
{
        struct snd_korg1212 *korg1212 = snd_pcm_substream_chip(substream);
	int rc;

	K1212_DEBUG_PRINTK("K1212_DEBUG: snd_korg1212_trigger [%s] cmd=%d\n",
			   stateName[korg1212->cardState], cmd);

	spin_lock(&korg1212->lock);
        switch (cmd) {
                case SNDRV_PCM_TRIGGER_START:
/*
			if (korg1212->running) {
				K1212_DEBUG_PRINTK_VERBOSE("K1212_DEBUG: snd_korg1212_trigger: Already running?\n");
				break;
			}
*/
                        korg1212->running++;
                        rc = snd_korg1212_TriggerPlay(korg1212);
                        break;

                case SNDRV_PCM_TRIGGER_STOP:
/*
			if (!korg1212->running) {
				K1212_DEBUG_PRINTK_VERBOSE("K1212_DEBUG: snd_korg1212_trigger: Already stopped?\n");
				break;
			}
*/
                        korg1212->running--;
                        rc = snd_korg1212_StopPlay(korg1212);
                        break;

                default:
			rc = 1;
			break;
        }
	spin_unlock(&korg1212->lock);
        return rc ? -EINVAL : 0;
}