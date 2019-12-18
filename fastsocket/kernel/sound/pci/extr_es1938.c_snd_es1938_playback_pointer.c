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
struct snd_pcm_substream {int number; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  snd_BUG () ; 
 int /*<<< orphan*/  snd_es1938_playback1_pointer (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_es1938_playback2_pointer (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_es1938_playback_pointer(struct snd_pcm_substream *substream)
{
	switch (substream->number) {
	case 0:
		return snd_es1938_playback1_pointer(substream);
	case 1:
		return snd_es1938_playback2_pointer(substream);
	}
	snd_BUG();
	return -EINVAL;
}