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
struct snd_korg1212 {size_t cardState; int channels; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 int /*<<< orphan*/  K1212_DEBUG_PRINTK_VERBOSE (char*,int /*<<< orphan*/ ) ; 
 int snd_korg1212_silence (struct snd_korg1212*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct snd_korg1212* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/ * stateName ; 

__attribute__((used)) static int snd_korg1212_playback_silence(struct snd_pcm_substream *substream,
                           int channel, /* not used (interleaved data) */
                           snd_pcm_uframes_t pos,
                           snd_pcm_uframes_t count)
{
        struct snd_korg1212 *korg1212 = snd_pcm_substream_chip(substream);

	K1212_DEBUG_PRINTK_VERBOSE("K1212_DEBUG: snd_korg1212_playback_silence [%s]\n",
				   stateName[korg1212->cardState]);

	return snd_korg1212_silence(korg1212, pos, count, 0, korg1212->channels * 2);
}