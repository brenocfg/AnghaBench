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
struct usX2Ydev {int wait_iso_frame; struct snd_usX2Y_substream** subs; int /*<<< orphan*/  dev; } ;
struct urb {int status; int start_frame; int /*<<< orphan*/  pipe; struct snd_usX2Y_substream* context; } ;
struct snd_usX2Y_substream {int /*<<< orphan*/  state; struct urb* completed_urb; int /*<<< orphan*/  endpoint; struct usX2Ydev* usX2Y; } ;

/* Variables and functions */
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ nr_of_packs () ; 
 int /*<<< orphan*/  snd_printdd (char*,...) ; 
 scalar_t__ state_PREPARED ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usX2Y_clients_stop (struct usX2Ydev*) ; 
 int /*<<< orphan*/  usX2Y_error_sequence (struct usX2Ydev*,struct snd_usX2Y_substream*,struct urb*) ; 
 int /*<<< orphan*/  usX2Y_error_urb_status (struct usX2Ydev*,struct snd_usX2Y_substream*,struct urb*) ; 
 int /*<<< orphan*/  usX2Y_usbpcm_usbframe_complete (struct snd_usX2Y_substream*,struct snd_usX2Y_substream*,struct snd_usX2Y_substream*,int) ; 
 int /*<<< orphan*/  usb_get_current_frame_number (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_pipein (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i_usX2Y_usbpcm_urb_complete(struct urb *urb)
{
	struct snd_usX2Y_substream *subs = urb->context;
	struct usX2Ydev *usX2Y = subs->usX2Y;
	struct snd_usX2Y_substream *capsubs, *capsubs2, *playbacksubs;

	if (unlikely(atomic_read(&subs->state) < state_PREPARED)) {
		snd_printdd("hcd_frame=%i ep=%i%s status=%i start_frame=%i\n",
			    usb_get_current_frame_number(usX2Y->dev),
			    subs->endpoint, usb_pipein(urb->pipe) ? "in" : "out",
			    urb->status, urb->start_frame);
		return;
	}
	if (unlikely(urb->status)) {
		usX2Y_error_urb_status(usX2Y, subs, urb);
		return;
	}
	if (likely((urb->start_frame & 0xFFFF) == (usX2Y->wait_iso_frame & 0xFFFF)))
		subs->completed_urb = urb;
	else {
		usX2Y_error_sequence(usX2Y, subs, urb);
		return;
	}

	capsubs = usX2Y->subs[SNDRV_PCM_STREAM_CAPTURE];
	capsubs2 = usX2Y->subs[SNDRV_PCM_STREAM_CAPTURE + 2];
	playbacksubs = usX2Y->subs[SNDRV_PCM_STREAM_PLAYBACK];
	if (capsubs->completed_urb && atomic_read(&capsubs->state) >= state_PREPARED &&
	    (NULL == capsubs2 || capsubs2->completed_urb) &&
	    (playbacksubs->completed_urb || atomic_read(&playbacksubs->state) < state_PREPARED)) {
		if (!usX2Y_usbpcm_usbframe_complete(capsubs, capsubs2, playbacksubs, urb->start_frame))
			usX2Y->wait_iso_frame += nr_of_packs();
		else {
			snd_printdd("\n");
			usX2Y_clients_stop(usX2Y);
		}
	}
}