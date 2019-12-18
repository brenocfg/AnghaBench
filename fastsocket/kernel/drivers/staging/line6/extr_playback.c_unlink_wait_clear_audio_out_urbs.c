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
struct snd_line6_pcm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  unlink_audio_out_urbs (struct snd_line6_pcm*) ; 
 int /*<<< orphan*/  wait_clear_audio_out_urbs (struct snd_line6_pcm*) ; 

void unlink_wait_clear_audio_out_urbs(struct snd_line6_pcm *line6pcm)
{
	unlink_audio_out_urbs(line6pcm);
	wait_clear_audio_out_urbs(line6pcm);
}