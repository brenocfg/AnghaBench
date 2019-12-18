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
struct urb {int dummy; } ;
struct snd_line6_pcm {struct urb** urb_audio_in; int /*<<< orphan*/  unlink_urb_in; int /*<<< orphan*/  active_urb_in; } ;

/* Variables and functions */
 unsigned int LINE6_ISO_BUFFERS ; 
 int /*<<< orphan*/  test_and_set_bit (unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_unlink_urb (struct urb*) ; 

__attribute__((used)) static void unlink_audio_in_urbs(struct snd_line6_pcm *line6pcm)
{
	unsigned int i;

	for (i = LINE6_ISO_BUFFERS; i--;) {
		if (test_bit(i, &line6pcm->active_urb_in)) {
			if (!test_and_set_bit(i, &line6pcm->unlink_urb_in)) {
				struct urb *u = line6pcm->urb_audio_in[i];
				usb_unlink_urb(u);
			}
		}
	}
}