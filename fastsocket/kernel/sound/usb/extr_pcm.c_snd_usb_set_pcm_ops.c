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
struct snd_pcm {int dummy; } ;

/* Variables and functions */
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_usb_capture_ops ; 
 int /*<<< orphan*/  snd_usb_playback_ops ; 

void snd_usb_set_pcm_ops(struct snd_pcm *pcm, int stream)
{
	snd_pcm_set_ops(pcm, stream,
			stream == SNDRV_PCM_STREAM_PLAYBACK ?
			&snd_usb_playback_ops : &snd_usb_capture_ops);
}