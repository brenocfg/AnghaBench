#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_14__ {scalar_t__ sample_number; } ;
struct TYPE_16__ {int blocksize; unsigned int channels; unsigned int bits_per_sample; int channel_assignment; scalar_t__ number_type; TYPE_1__ number; int /*<<< orphan*/  sample_rate; } ;
struct TYPE_19__ {TYPE_3__ header; } ;
struct TYPE_18__ {TYPE_2__* protected_; TYPE_4__* private_; } ;
struct TYPE_17__ {int** output; TYPE_7__ frame; scalar_t__ samples_decoded; scalar_t__ next_fixed_block_size; scalar_t__ fixed_block_size; int /*<<< orphan*/  input; int /*<<< orphan*/ * header_warmup; } ;
struct TYPE_15__ {scalar_t__ state; unsigned int channels; int channel_assignment; unsigned int bits_per_sample; int blocksize; int /*<<< orphan*/  sample_rate; } ;
typedef  unsigned int FLAC__uint32 ;
typedef  int /*<<< orphan*/  FLAC__uint16 ;
typedef  int FLAC__int32 ;
typedef  int FLAC__bool ;
typedef  TYPE_5__ FLAC__StreamDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC__ASSERT (int) ; 
#define  FLAC__CHANNEL_ASSIGNMENT_INDEPENDENT 131 
#define  FLAC__CHANNEL_ASSIGNMENT_LEFT_SIDE 130 
#define  FLAC__CHANNEL_ASSIGNMENT_MID_SIDE 129 
#define  FLAC__CHANNEL_ASSIGNMENT_RIGHT_SIDE 128 
 unsigned int FLAC__CRC16_UPDATE (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  FLAC__FRAME_FOOTER_CRC_LEN ; 
 scalar_t__ FLAC__FRAME_NUMBER_TYPE_SAMPLE_NUMBER ; 
 scalar_t__ FLAC__STREAM_DECODER_ABORTED ; 
 int /*<<< orphan*/  FLAC__STREAM_DECODER_ERROR_STATUS_FRAME_CRC_MISMATCH ; 
 scalar_t__ FLAC__STREAM_DECODER_SEARCH_FOR_FRAME_SYNC ; 
 scalar_t__ FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE ; 
 unsigned int FLAC__bitreader_get_read_crc16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLAC__bitreader_read_raw_uint32 (int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLAC__bitreader_reset_read_crc16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  allocate_output_ (TYPE_5__*,int,unsigned int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_frame_header_ (TYPE_5__*) ; 
 int /*<<< orphan*/  read_subframe_ (TYPE_5__*,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  read_zero_padding_ (TYPE_5__*) ; 
 int /*<<< orphan*/  send_error_to_client_ (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ write_audio_frame_to_client_ (TYPE_5__*,TYPE_7__*,int const* const*) ; 

FLAC__bool read_frame_(FLAC__StreamDecoder *decoder, FLAC__bool *got_a_frame, FLAC__bool do_full_decode)
{
	unsigned channel;
	unsigned i;
	FLAC__int32 mid, side;
	unsigned frame_crc; /* the one we calculate from the input stream */
	FLAC__uint32 x;

	*got_a_frame = false;

	/* init the CRC */
	frame_crc = 0;
	frame_crc = FLAC__CRC16_UPDATE(decoder->private_->header_warmup[0], frame_crc);
	frame_crc = FLAC__CRC16_UPDATE(decoder->private_->header_warmup[1], frame_crc);
	FLAC__bitreader_reset_read_crc16(decoder->private_->input, (FLAC__uint16)frame_crc);

	if(!read_frame_header_(decoder))
		return false;
	if(decoder->protected_->state == FLAC__STREAM_DECODER_SEARCH_FOR_FRAME_SYNC) /* means we didn't sync on a valid header */
		return true;
	if(!allocate_output_(decoder, decoder->private_->frame.header.blocksize, decoder->private_->frame.header.channels))
		return false;
	for(channel = 0; channel < decoder->private_->frame.header.channels; channel++) {
		/*
		 * first figure the correct bits-per-sample of the subframe
		 */
		unsigned bps = decoder->private_->frame.header.bits_per_sample;
		switch(decoder->private_->frame.header.channel_assignment) {
			case FLAC__CHANNEL_ASSIGNMENT_INDEPENDENT:
				/* no adjustment needed */
				break;
			case FLAC__CHANNEL_ASSIGNMENT_LEFT_SIDE:
				FLAC__ASSERT(decoder->private_->frame.header.channels == 2);
				if(channel == 1)
					bps++;
				break;
			case FLAC__CHANNEL_ASSIGNMENT_RIGHT_SIDE:
				FLAC__ASSERT(decoder->private_->frame.header.channels == 2);
				if(channel == 0)
					bps++;
				break;
			case FLAC__CHANNEL_ASSIGNMENT_MID_SIDE:
				FLAC__ASSERT(decoder->private_->frame.header.channels == 2);
				if(channel == 1)
					bps++;
				break;
			default:
				FLAC__ASSERT(0);
		}
		/*
		 * now read it
		 */
		if(!read_subframe_(decoder, channel, bps, do_full_decode))
			return false;
		if(decoder->protected_->state == FLAC__STREAM_DECODER_SEARCH_FOR_FRAME_SYNC) /* means bad sync or got corruption */
			return true;
	}
	if(!read_zero_padding_(decoder))
		return false;
	if(decoder->protected_->state == FLAC__STREAM_DECODER_SEARCH_FOR_FRAME_SYNC) /* means bad sync or got corruption (i.e. "zero bits" were not all zeroes) */
		return true;

	/*
	 * Read the frame CRC-16 from the footer and check
	 */
	frame_crc = FLAC__bitreader_get_read_crc16(decoder->private_->input);
	if(!FLAC__bitreader_read_raw_uint32(decoder->private_->input, &x, FLAC__FRAME_FOOTER_CRC_LEN))
		return false; /* read_callback_ sets the state for us */
	if(frame_crc == x) {
		if(do_full_decode) {
			/* Undo any special channel coding */
			switch(decoder->private_->frame.header.channel_assignment) {
				case FLAC__CHANNEL_ASSIGNMENT_INDEPENDENT:
					/* do nothing */
					break;
				case FLAC__CHANNEL_ASSIGNMENT_LEFT_SIDE:
					FLAC__ASSERT(decoder->private_->frame.header.channels == 2);
					for(i = 0; i < decoder->private_->frame.header.blocksize; i++)
						decoder->private_->output[1][i] = decoder->private_->output[0][i] - decoder->private_->output[1][i];
					break;
				case FLAC__CHANNEL_ASSIGNMENT_RIGHT_SIDE:
					FLAC__ASSERT(decoder->private_->frame.header.channels == 2);
					for(i = 0; i < decoder->private_->frame.header.blocksize; i++)
						decoder->private_->output[0][i] += decoder->private_->output[1][i];
					break;
				case FLAC__CHANNEL_ASSIGNMENT_MID_SIDE:
					FLAC__ASSERT(decoder->private_->frame.header.channels == 2);
					for(i = 0; i < decoder->private_->frame.header.blocksize; i++) {
#if 1
						mid = decoder->private_->output[0][i];
						side = decoder->private_->output[1][i];
						mid = ((uint32_t) mid) << 1;
						mid |= (side & 1); /* i.e. if 'side' is odd... */
						decoder->private_->output[0][i] = (mid + side) >> 1;
						decoder->private_->output[1][i] = (mid - side) >> 1;
#else
						/* OPT: without 'side' temp variable */
						mid = (decoder->private_->output[0][i] << 1) | (decoder->private_->output[1][i] & 1); /* i.e. if 'side' is odd... */
						decoder->private_->output[0][i] = (mid + decoder->private_->output[1][i]) >> 1;
						decoder->private_->output[1][i] = (mid - decoder->private_->output[1][i]) >> 1;
#endif
					}
					break;
				default:
					FLAC__ASSERT(0);
					break;
			}
		}
	}
	else {
		/* Bad frame, emit error and zero the output signal */
		send_error_to_client_(decoder, FLAC__STREAM_DECODER_ERROR_STATUS_FRAME_CRC_MISMATCH);
		if(do_full_decode) {
			for(channel = 0; channel < decoder->private_->frame.header.channels; channel++) {
				memset(decoder->private_->output[channel], 0, sizeof(FLAC__int32) * decoder->private_->frame.header.blocksize);
			}
		}
	}

	*got_a_frame = true;

	/* we wait to update fixed_block_size until here, when we're sure we've got a proper frame and hence a correct blocksize */
	if(decoder->private_->next_fixed_block_size)
		decoder->private_->fixed_block_size = decoder->private_->next_fixed_block_size;

	/* put the latest values into the public section of the decoder instance */
	decoder->protected_->channels = decoder->private_->frame.header.channels;
	decoder->protected_->channel_assignment = decoder->private_->frame.header.channel_assignment;
	decoder->protected_->bits_per_sample = decoder->private_->frame.header.bits_per_sample;
	decoder->protected_->sample_rate = decoder->private_->frame.header.sample_rate;
	decoder->protected_->blocksize = decoder->private_->frame.header.blocksize;

	FLAC__ASSERT(decoder->private_->frame.header.number_type == FLAC__FRAME_NUMBER_TYPE_SAMPLE_NUMBER);
	decoder->private_->samples_decoded = decoder->private_->frame.header.number.sample_number + decoder->private_->frame.header.blocksize;

	/* write it */
	if(do_full_decode) {
		if(write_audio_frame_to_client_(decoder, &decoder->private_->frame, (const FLAC__int32 * const *)decoder->private_->output) != FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE) {
			decoder->protected_->state = FLAC__STREAM_DECODER_ABORTED;
			return false;
		}
	}

	decoder->protected_->state = FLAC__STREAM_DECODER_SEARCH_FOR_FRAME_SYNC;
	return true;
}