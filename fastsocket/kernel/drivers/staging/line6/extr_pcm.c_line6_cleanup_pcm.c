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
struct snd_line6_pcm {scalar_t__* urb_audio_in; scalar_t__* urb_audio_out; } ;

/* Variables and functions */
 int LINE6_ISO_BUFFERS ; 
 struct snd_line6_pcm* snd_pcm_chip (struct snd_pcm*) ; 
 int /*<<< orphan*/  usb_free_urb (scalar_t__) ; 
 int /*<<< orphan*/  usb_kill_urb (scalar_t__) ; 

__attribute__((used)) static void line6_cleanup_pcm(struct snd_pcm *pcm)
{
	int i;
	struct snd_line6_pcm *line6pcm = snd_pcm_chip(pcm);

	for (i = LINE6_ISO_BUFFERS; i--;) {
		if (line6pcm->urb_audio_out[i]) {
			usb_kill_urb(line6pcm->urb_audio_out[i]);
			usb_free_urb(line6pcm->urb_audio_out[i]);
		}
		if (line6pcm->urb_audio_in[i]) {
			usb_kill_urb(line6pcm->urb_audio_in[i]);
			usb_free_urb(line6pcm->urb_audio_in[i]);
		}
	}
}