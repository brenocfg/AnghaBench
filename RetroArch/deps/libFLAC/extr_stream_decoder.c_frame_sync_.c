#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* protected_; TYPE_1__* private_; } ;
struct TYPE_8__ {int /*<<< orphan*/  state; } ;
struct TYPE_7__ {scalar_t__ samples_decoded; int cached; void** header_warmup; void* lookahead; int /*<<< orphan*/  input; } ;
typedef  int FLAC__uint32 ;
typedef  void* FLAC__byte ;
typedef  int FLAC__bool ;
typedef  TYPE_3__ FLAC__StreamDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC__STREAM_DECODER_END_OF_STREAM ; 
 int /*<<< orphan*/  FLAC__STREAM_DECODER_ERROR_STATUS_LOST_SYNC ; 
 int /*<<< orphan*/  FLAC__STREAM_DECODER_READ_FRAME ; 
 int FLAC__bitreader_bits_left_for_byte_alignment (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLAC__bitreader_is_consumed_byte_aligned (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLAC__bitreader_read_raw_uint32 (int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ FLAC__stream_decoder_get_total_samples (TYPE_3__*) ; 
 int /*<<< orphan*/  send_error_to_client_ (TYPE_3__*,int /*<<< orphan*/ ) ; 

FLAC__bool frame_sync_(FLAC__StreamDecoder *decoder)
{
	FLAC__uint32 x;
	FLAC__bool first = true;

	/* If we know the total number of samples in the stream, stop if we've read that many. */
	/* This will stop us, for example, from wasting time trying to sync on an ID3V1 tag. */
	if(FLAC__stream_decoder_get_total_samples(decoder) > 0) {
		if(decoder->private_->samples_decoded >= FLAC__stream_decoder_get_total_samples(decoder)) {
			decoder->protected_->state = FLAC__STREAM_DECODER_END_OF_STREAM;
			return true;
		}
	}

	/* make sure we're byte aligned */
	if(!FLAC__bitreader_is_consumed_byte_aligned(decoder->private_->input)) {
		if(!FLAC__bitreader_read_raw_uint32(decoder->private_->input, &x, FLAC__bitreader_bits_left_for_byte_alignment(decoder->private_->input)))
			return false; /* read_callback_ sets the state for us */
	}

	while(1) {
		if(decoder->private_->cached) {
			x = (FLAC__uint32)decoder->private_->lookahead;
			decoder->private_->cached = false;
		}
		else {
			if(!FLAC__bitreader_read_raw_uint32(decoder->private_->input, &x, 8))
				return false; /* read_callback_ sets the state for us */
		}
		if(x == 0xff) { /* MAGIC NUMBER for the first 8 frame sync bits */
			decoder->private_->header_warmup[0] = (FLAC__byte)x;
			if(!FLAC__bitreader_read_raw_uint32(decoder->private_->input, &x, 8))
				return false; /* read_callback_ sets the state for us */

			/* we have to check if we just read two 0xff's in a row; the second may actually be the beginning of the sync code */
			/* else we have to check if the second byte is the end of a sync code */
			if(x == 0xff) { /* MAGIC NUMBER for the first 8 frame sync bits */
				decoder->private_->lookahead = (FLAC__byte)x;
				decoder->private_->cached = true;
			}
			else if(x >> 1 == 0x7c) { /* MAGIC NUMBER for the last 6 sync bits and reserved 7th bit */
				decoder->private_->header_warmup[1] = (FLAC__byte)x;
				decoder->protected_->state = FLAC__STREAM_DECODER_READ_FRAME;
				return true;
			}
		}
		if(first) {
			send_error_to_client_(decoder, FLAC__STREAM_DECODER_ERROR_STATUS_LOST_SYNC);
			first = false;
		}
	}

	return true;
}