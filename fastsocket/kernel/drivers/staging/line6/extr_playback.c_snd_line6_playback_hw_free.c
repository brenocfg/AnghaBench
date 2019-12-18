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
struct snd_line6_pcm {int /*<<< orphan*/ * wrap_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 
 struct snd_line6_pcm* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  unlink_wait_clear_audio_out_urbs (struct snd_line6_pcm*) ; 

__attribute__((used)) static int snd_line6_playback_hw_free(struct snd_pcm_substream *substream)
{
	struct snd_line6_pcm *line6pcm = snd_pcm_substream_chip(substream);
	unlink_wait_clear_audio_out_urbs(line6pcm);

	kfree(line6pcm->wrap_out);
	line6pcm->wrap_out = NULL;

	return snd_pcm_lib_free_pages(substream);
}