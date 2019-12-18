#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct snd_mixart {TYPE_2__* mgr; } ;
struct mixart_stream {TYPE_4__* pipe; } ;
struct TYPE_7__ {int references; } ;
struct TYPE_6__ {int ref_count_rate; int /*<<< orphan*/  sample_rate; } ;
struct TYPE_5__ {int /*<<< orphan*/  rate; struct mixart_stream* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ mixart_set_clock (TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mixart_sync_nonblock_events (TYPE_2__*) ; 
 struct snd_mixart* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_printdd (char*) ; 

__attribute__((used)) static int snd_mixart_prepare(struct snd_pcm_substream *subs)
{
	struct snd_mixart *chip = snd_pcm_substream_chip(subs);
	struct mixart_stream *stream = subs->runtime->private_data;

	/* TODO de façon non bloquante, réappliquer les hw_params (rate, bits, codec) */

	snd_printdd("snd_mixart_prepare\n");

	mixart_sync_nonblock_events(chip->mgr);

	/* only the first stream can choose the sample rate */
	/* the further opened streams will be limited to its frequency (see open) */
	if(chip->mgr->ref_count_rate == 1)
		chip->mgr->sample_rate = subs->runtime->rate;

	/* set the clock only once (first stream) on the same pipe */
	if(stream->pipe->references == 1) {
		if( mixart_set_clock(chip->mgr, stream->pipe, subs->runtime->rate) )
			return -EINVAL;
	}

	return 0;
}