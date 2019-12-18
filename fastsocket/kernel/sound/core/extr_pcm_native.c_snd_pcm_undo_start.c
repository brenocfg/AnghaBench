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
struct snd_pcm_substream {TYPE_2__* ops; TYPE_1__* runtime; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* trigger ) (struct snd_pcm_substream*,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {struct snd_pcm_substream* trigger_master; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_TRIGGER_STOP ; 
 int /*<<< orphan*/  stub1 (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_pcm_undo_start(struct snd_pcm_substream *substream, int state)
{
	if (substream->runtime->trigger_master == substream)
		substream->ops->trigger(substream, SNDRV_PCM_TRIGGER_STOP);
}