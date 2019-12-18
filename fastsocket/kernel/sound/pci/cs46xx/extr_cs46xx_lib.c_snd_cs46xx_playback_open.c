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
 int /*<<< orphan*/  DSP_PCM_MAIN_CHANNEL ; 
 int _cs46xx_playback_open_channel (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_printdd (char*) ; 

__attribute__((used)) static int snd_cs46xx_playback_open(struct snd_pcm_substream *substream)
{
	snd_printdd("open front channel\n");
	return _cs46xx_playback_open_channel(substream,DSP_PCM_MAIN_CHANNEL);
}