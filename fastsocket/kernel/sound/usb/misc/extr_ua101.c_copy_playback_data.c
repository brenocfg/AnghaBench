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
typedef  int /*<<< orphan*/  const u8 ;
struct urb {scalar_t__ transfer_buffer; } ;
struct ua101_stream {unsigned int frame_bytes; unsigned int buffer_pos; scalar_t__ period_pos; TYPE_1__* substream; } ;
struct snd_pcm_runtime {unsigned int buffer_size; scalar_t__ period_size; int /*<<< orphan*/  const* dma_area; } ;
struct TYPE_2__ {struct snd_pcm_runtime* runtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static bool copy_playback_data(struct ua101_stream *stream, struct urb *urb,
			       unsigned int frames)
{
	struct snd_pcm_runtime *runtime;
	unsigned int frame_bytes, frames1;
	const u8 *source;

	runtime = stream->substream->runtime;
	frame_bytes = stream->frame_bytes;
	source = runtime->dma_area + stream->buffer_pos * frame_bytes;
	if (stream->buffer_pos + frames <= runtime->buffer_size) {
		memcpy(urb->transfer_buffer, source, frames * frame_bytes);
	} else {
		/* wrap around at end of ring buffer */
		frames1 = runtime->buffer_size - stream->buffer_pos;
		memcpy(urb->transfer_buffer, source, frames1 * frame_bytes);
		memcpy(urb->transfer_buffer + frames1 * frame_bytes,
		       runtime->dma_area, (frames - frames1) * frame_bytes);
	}

	stream->buffer_pos += frames;
	if (stream->buffer_pos >= runtime->buffer_size)
		stream->buffer_pos -= runtime->buffer_size;
	stream->period_pos += frames;
	if (stream->period_pos >= runtime->period_size) {
		stream->period_pos -= runtime->period_size;
		return true;
	}
	return false;
}