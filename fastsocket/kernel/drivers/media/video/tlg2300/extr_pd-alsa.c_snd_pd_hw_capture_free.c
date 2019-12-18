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
struct poseidon {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  audio_buf_free (struct poseidon*) ; 
 int /*<<< orphan*/  logpm () ; 
 struct poseidon* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_pd_hw_capture_free(struct snd_pcm_substream *substream)
{
	struct poseidon *p = snd_pcm_substream_chip(substream);

	logpm();
	audio_buf_free(p);
	return 0;
}