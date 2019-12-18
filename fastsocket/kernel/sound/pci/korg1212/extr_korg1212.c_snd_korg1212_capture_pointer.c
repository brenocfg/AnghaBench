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
struct snd_korg1212 {int currentBuffer; size_t cardState; } ;
typedef  int snd_pcm_uframes_t ;

/* Variables and functions */
 int /*<<< orphan*/  K1212_DEBUG_PRINTK_VERBOSE (char*,int /*<<< orphan*/ ,int) ; 
 int kPlayBufferFrames ; 
 struct snd_korg1212* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/ * stateName ; 

__attribute__((used)) static snd_pcm_uframes_t snd_korg1212_capture_pointer(struct snd_pcm_substream *substream)
{
        struct snd_korg1212 *korg1212 = snd_pcm_substream_chip(substream);
        snd_pcm_uframes_t pos;

	pos = korg1212->currentBuffer * kPlayBufferFrames;

	K1212_DEBUG_PRINTK_VERBOSE("K1212_DEBUG: snd_korg1212_capture_pointer [%s] %ld\n",
				   stateName[korg1212->cardState], pos);

        return pos;
}