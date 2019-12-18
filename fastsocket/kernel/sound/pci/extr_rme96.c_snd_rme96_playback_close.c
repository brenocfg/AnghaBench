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
struct snd_pcm_substream {int dummy; } ;
struct rme96 {int wcreg; TYPE_2__* spdif_ctl; int /*<<< orphan*/  card; int /*<<< orphan*/  lock; scalar_t__ playback_periodsize; int /*<<< orphan*/ * playback_substream; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; TYPE_1__* vd; } ;
struct TYPE_3__ {int /*<<< orphan*/  access; } ;

/* Variables and functions */
 scalar_t__ RME96_ISPLAYING (struct rme96*) ; 
 int RME96_WCR_ADAT ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_ACCESS_INACTIVE ; 
 int SNDRV_CTL_EVENT_MASK_INFO ; 
 int SNDRV_CTL_EVENT_MASK_VALUE ; 
 int /*<<< orphan*/  snd_ctl_notify (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct rme96* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_rme96_playback_stop (struct rme96*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
snd_rme96_playback_close(struct snd_pcm_substream *substream)
{
	struct rme96 *rme96 = snd_pcm_substream_chip(substream);
	int spdif = 0;

	spin_lock_irq(&rme96->lock);	
	if (RME96_ISPLAYING(rme96)) {
		snd_rme96_playback_stop(rme96);
	}
	rme96->playback_substream = NULL;
	rme96->playback_periodsize = 0;
	spdif = (rme96->wcreg & RME96_WCR_ADAT) == 0;
	spin_unlock_irq(&rme96->lock);
	if (spdif) {
		rme96->spdif_ctl->vd[0].access |= SNDRV_CTL_ELEM_ACCESS_INACTIVE;
		snd_ctl_notify(rme96->card, SNDRV_CTL_EVENT_MASK_VALUE |
			       SNDRV_CTL_EVENT_MASK_INFO, &rme96->spdif_ctl->id);
	}
	return 0;
}