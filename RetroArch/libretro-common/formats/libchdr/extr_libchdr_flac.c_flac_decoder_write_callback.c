#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  void* int16_t ;
struct TYPE_6__ {int channels; void*** uncompressed_start; int uncompressed_offset; int uncompressed_length; scalar_t__ uncompressed_swap; } ;
typedef  TYPE_2__ flac_decoder ;
struct TYPE_5__ {int channels; int blocksize; } ;
struct TYPE_7__ {TYPE_1__ header; } ;
typedef  scalar_t__ FLAC__int32 ;
typedef  int /*<<< orphan*/  FLAC__StreamDecoderWriteStatus ;
typedef  TYPE_3__ FLAC__Frame ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE ; 
 int /*<<< orphan*/  assert (int) ; 

FLAC__StreamDecoderWriteStatus flac_decoder_write_callback(void *client_data, const FLAC__Frame *frame, const FLAC__int32 * const buffer[])
{
	int sampnum, chan;
   int shift, blocksize;
	flac_decoder * decoder = (flac_decoder *)client_data;

	assert(frame->header.channels == decoder->channels);

	/* interleaved case */
	shift = decoder->uncompressed_swap ? 8 : 0;
	blocksize = frame->header.blocksize;
	if (decoder->uncompressed_start[1] == NULL)
	{
		int16_t *dest = decoder->uncompressed_start[0] + decoder->uncompressed_offset * frame->header.channels;
		for (sampnum = 0; sampnum < blocksize && decoder->uncompressed_offset < decoder->uncompressed_length; sampnum++, decoder->uncompressed_offset++)
			for (chan = 0; chan < frame->header.channels; chan++)
				*dest++ = (int16_t)((((uint16_t)buffer[chan][sampnum]) << shift) | (((uint16_t)buffer[chan][sampnum]) >> shift));
	}

	/* non-interleaved case */
	else
	{
		for (sampnum = 0; sampnum < blocksize && decoder->uncompressed_offset < decoder->uncompressed_length; sampnum++, decoder->uncompressed_offset++)
			for (chan = 0; chan < frame->header.channels; chan++)
				if (decoder->uncompressed_start[chan] != NULL)
					decoder->uncompressed_start[chan][decoder->uncompressed_offset] = (int16_t) ( (((uint16_t)(buffer[chan][sampnum])) << shift) | ( ((uint16_t)(buffer[chan][sampnum])) >> shift) );
	}
	return FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE;
}