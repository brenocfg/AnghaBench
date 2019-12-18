#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct loopback_setup {int dummy; } ;
struct loopback_pcm {TYPE_4__* substream; TYPE_3__* loopback; } ;
struct TYPE_8__ {scalar_t__ stream; size_t number; TYPE_2__* pstr; } ;
struct TYPE_7__ {struct loopback_setup** setup; } ;
struct TYPE_6__ {TYPE_1__* pcm; } ;
struct TYPE_5__ {int device; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 

__attribute__((used)) static inline struct loopback_setup *get_setup(struct loopback_pcm *dpcm)
{
	int device = dpcm->substream->pstr->pcm->device;
	
	if (dpcm->substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		device ^= 1;
	return &dpcm->loopback->setup[dpcm->substream->number][device];
}