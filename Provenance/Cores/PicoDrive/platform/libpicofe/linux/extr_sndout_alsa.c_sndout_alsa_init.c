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

/* Variables and functions */
 int /*<<< orphan*/  SND_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  handle ; 
 int snd_pcm_open (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sndout_alsa_init(void)
{
	int ret;

	ret = snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
	if (ret != 0)
		return -1;

	return 0;
}