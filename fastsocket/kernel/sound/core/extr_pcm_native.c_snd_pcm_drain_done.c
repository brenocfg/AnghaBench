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

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_STATE_SETUP ; 
 int snd_pcm_action_single (int /*<<< orphan*/ *,struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_action_stop ; 

int snd_pcm_drain_done(struct snd_pcm_substream *substream)
{
	return snd_pcm_action_single(&snd_pcm_action_stop, substream,
				     SNDRV_PCM_STATE_SETUP);
}