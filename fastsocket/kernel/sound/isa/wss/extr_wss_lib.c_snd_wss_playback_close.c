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
struct snd_wss {int /*<<< orphan*/ * playback_substream; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WSS_MODE_PLAY ; 
 struct snd_wss* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_wss_close (struct snd_wss*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_wss_playback_close(struct snd_pcm_substream *substream)
{
	struct snd_wss *chip = snd_pcm_substream_chip(substream);

	chip->playback_substream = NULL;
	snd_wss_close(chip, WSS_MODE_PLAY);
	return 0;
}