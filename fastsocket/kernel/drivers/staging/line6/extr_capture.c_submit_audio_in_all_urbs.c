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
 int LINE6_ISO_BUFFERS ; 
 int submit_audio_in_urb (struct snd_pcm_substream*) ; 

__attribute__((used)) static int submit_audio_in_all_urbs(struct snd_pcm_substream *substream)
{
	int ret, i;

	for (i = 0; i < LINE6_ISO_BUFFERS; ++i) {
		ret = submit_audio_in_urb(substream);
		if (ret < 0)
			return ret;
	}

	return 0;
}