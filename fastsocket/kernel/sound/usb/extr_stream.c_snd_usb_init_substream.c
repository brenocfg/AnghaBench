#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_usb_substream {int direction; int /*<<< orphan*/  ep_num; int /*<<< orphan*/  fmt_type; int /*<<< orphan*/  num_formats; int /*<<< orphan*/  formats; int /*<<< orphan*/  fmt_list; int /*<<< orphan*/  txfr_quirk; int /*<<< orphan*/  dev; struct snd_usb_stream* stream; int /*<<< orphan*/  lock; } ;
struct snd_usb_stream {int /*<<< orphan*/  pcm; TYPE_1__* chip; struct snd_usb_substream* substream; } ;
struct audioformat {int /*<<< orphan*/  endpoint; int /*<<< orphan*/  fmt_type; int /*<<< orphan*/  formats; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  txfr_quirk; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_usb_set_pcm_ops (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_usb_init_substream(struct snd_usb_stream *as,
				   int stream,
				   struct audioformat *fp)
{
	struct snd_usb_substream *subs = &as->substream[stream];

	INIT_LIST_HEAD(&subs->fmt_list);
	spin_lock_init(&subs->lock);

	subs->stream = as;
	subs->direction = stream;
	subs->dev = as->chip->dev;
	subs->txfr_quirk = as->chip->txfr_quirk;

	snd_usb_set_pcm_ops(as->pcm, stream);

	list_add_tail(&fp->list, &subs->fmt_list);
	subs->formats |= fp->formats;
	subs->num_formats++;
	subs->fmt_type = fp->fmt_type;
	subs->ep_num = fp->endpoint;
}