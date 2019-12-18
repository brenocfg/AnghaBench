#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_13__ ;
typedef  struct TYPE_24__   TYPE_12__ ;
typedef  struct TYPE_23__   TYPE_11__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
struct TYPE_33__ {unsigned int min_blocksize; unsigned int max_blocksize; unsigned int max_framesize; unsigned int min_framesize; unsigned int channels; unsigned int bits_per_sample; } ;
struct TYPE_34__ {TYPE_8__ stream_info; } ;
struct TYPE_24__ {TYPE_1__* points; scalar_t__ num_points; } ;
struct TYPE_31__ {TYPE_12__ seek_table; } ;
struct TYPE_32__ {TYPE_6__ data; } ;
struct TYPE_30__ {scalar_t__ state; } ;
struct TYPE_27__ {scalar_t__ sample_number; } ;
struct TYPE_28__ {scalar_t__ number_type; scalar_t__ blocksize; TYPE_2__ number; } ;
struct TYPE_29__ {TYPE_3__ header; } ;
struct TYPE_26__ {scalar_t__ sample_number; scalar_t__ frame_samples; scalar_t__ stream_offset; } ;
struct TYPE_25__ {TYPE_5__* protected_; TYPE_11__* private_; } ;
struct TYPE_22__ {TYPE_9__ data; } ;
struct TYPE_23__ {scalar_t__ first_frame_offset; scalar_t__ (* seek_callback ) (TYPE_13__*,scalar_t__,int /*<<< orphan*/ ) ;scalar_t__ samples_decoded; TYPE_4__ last_frame; int /*<<< orphan*/  is_seeking; scalar_t__ unparseable_frame_count; int /*<<< orphan*/  client_data; scalar_t__ target_sample; TYPE_10__ stream_info; TYPE_7__ seek_table; scalar_t__ has_seek_table; } ;
typedef  scalar_t__ FLAC__uint64 ;
typedef  scalar_t__ FLAC__int64 ;
typedef  int FLAC__bool ;
typedef  TYPE_12__ FLAC__StreamMetadata_SeekTable ;
typedef  TYPE_13__ FLAC__StreamDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC__ASSERT (int) ; 
 scalar_t__ FLAC__FRAME_NUMBER_TYPE_SAMPLE_NUMBER ; 
 scalar_t__ FLAC__SEEKABLE_STREAM_DECODER_SEEKING ; 
 scalar_t__ FLAC__STREAM_DECODER_ABORTED ; 
 scalar_t__ FLAC__STREAM_DECODER_END_OF_STREAM ; 
 void* FLAC__STREAM_DECODER_SEEK_ERROR ; 
 scalar_t__ FLAC__STREAM_DECODER_SEEK_STATUS_OK ; 
 scalar_t__ FLAC__STREAM_METADATA_SEEKPOINT_PLACEHOLDER ; 
 int /*<<< orphan*/  FLAC__stream_decoder_flush (TYPE_13__*) ; 
 unsigned int FLAC__stream_decoder_get_bits_per_sample (TYPE_13__*) ; 
 unsigned int FLAC__stream_decoder_get_channels (TYPE_13__*) ; 
 int /*<<< orphan*/  FLAC__stream_decoder_get_decode_position (TYPE_13__*,scalar_t__*) ; 
 scalar_t__ FLAC__stream_decoder_get_total_samples (TYPE_13__*) ; 
 int /*<<< orphan*/  FLAC__stream_decoder_process_single (TYPE_13__*) ; 
 scalar_t__ stub1 (TYPE_13__*,scalar_t__,int /*<<< orphan*/ ) ; 

FLAC__bool seek_to_absolute_sample_(FLAC__StreamDecoder *decoder, FLAC__uint64 stream_length, FLAC__uint64 target_sample)
{
	FLAC__uint64 first_frame_offset = decoder->private_->first_frame_offset, lower_bound, upper_bound, lower_bound_sample, upper_bound_sample, this_frame_sample;
	FLAC__int64 pos = -1;
	int i;
	unsigned approx_bytes_per_frame;
	FLAC__bool first_seek = true;
	const FLAC__uint64 total_samples = FLAC__stream_decoder_get_total_samples(decoder);
	const unsigned min_blocksize = decoder->private_->stream_info.data.stream_info.min_blocksize;
	const unsigned max_blocksize = decoder->private_->stream_info.data.stream_info.max_blocksize;
	const unsigned max_framesize = decoder->private_->stream_info.data.stream_info.max_framesize;
	const unsigned min_framesize = decoder->private_->stream_info.data.stream_info.min_framesize;
	/* take these from the current frame in case they've changed mid-stream */
	unsigned channels = FLAC__stream_decoder_get_channels(decoder);
	unsigned bps = FLAC__stream_decoder_get_bits_per_sample(decoder);
	const FLAC__StreamMetadata_SeekTable *seek_table = decoder->private_->has_seek_table? &decoder->private_->seek_table.data.seek_table : 0;

	/* use values from stream info if we didn't decode a frame */
	if(channels == 0)
		channels = decoder->private_->stream_info.data.stream_info.channels;
	if(bps == 0)
		bps = decoder->private_->stream_info.data.stream_info.bits_per_sample;

	/* we are just guessing here */
	if(max_framesize > 0)
		approx_bytes_per_frame = (max_framesize + min_framesize) / 2 + 1;
	/*
	 * Check if it's a known fixed-blocksize stream.  Note that though
	 * the spec doesn't allow zeroes in the STREAMINFO block, we may
	 * never get a STREAMINFO block when decoding so the value of
	 * min_blocksize might be zero.
	 */
	else if(min_blocksize == max_blocksize && min_blocksize > 0) {
		/* note there are no () around 'bps/8' to keep precision up since it's an integer calulation */
		approx_bytes_per_frame = min_blocksize * channels * bps/8 + 64;
	}
	else
		approx_bytes_per_frame = 4096 * channels * bps/8 + 64;

	/*
	 * First, we set an upper and lower bound on where in the
	 * stream we will search.  For now we assume the worst case
	 * scenario, which is our best guess at the beginning of
	 * the first frame and end of the stream.
	 */
	lower_bound = first_frame_offset;
	lower_bound_sample = 0;
	upper_bound = stream_length;
	upper_bound_sample = total_samples > 0 ? total_samples : target_sample /*estimate it*/;

	/*
	 * Now we refine the bounds if we have a seektable with
	 * suitable points.  Note that according to the spec they
	 * must be ordered by ascending sample number.
	 *
	 * Note: to protect against invalid seek tables we will ignore points
	 * that have frame_samples==0 or sample_number>=total_samples
	 */
	if(seek_table) {
		FLAC__uint64 new_lower_bound = lower_bound;
		FLAC__uint64 new_upper_bound = upper_bound;
		FLAC__uint64 new_lower_bound_sample = lower_bound_sample;
		FLAC__uint64 new_upper_bound_sample = upper_bound_sample;

		/* find the closest seek point <= target_sample, if it exists */
		for(i = (int)seek_table->num_points - 1; i >= 0; i--) {
			if(
				seek_table->points[i].sample_number != FLAC__STREAM_METADATA_SEEKPOINT_PLACEHOLDER &&
				seek_table->points[i].frame_samples > 0 && /* defense against bad seekpoints */
				(total_samples <= 0 || seek_table->points[i].sample_number < total_samples) && /* defense against bad seekpoints */
				seek_table->points[i].sample_number <= target_sample
			)
				break;
		}
		if(i >= 0) { /* i.e. we found a suitable seek point... */
			new_lower_bound = first_frame_offset + seek_table->points[i].stream_offset;
			new_lower_bound_sample = seek_table->points[i].sample_number;
		}

		/* find the closest seek point > target_sample, if it exists */
		for(i = 0; i < (int)seek_table->num_points; i++) {
			if(
				seek_table->points[i].sample_number != FLAC__STREAM_METADATA_SEEKPOINT_PLACEHOLDER &&
				seek_table->points[i].frame_samples > 0 && /* defense against bad seekpoints */
				(total_samples <= 0 || seek_table->points[i].sample_number < total_samples) && /* defense against bad seekpoints */
				seek_table->points[i].sample_number > target_sample
			)
				break;
		}
		if(i < (int)seek_table->num_points) { /* i.e. we found a suitable seek point... */
			new_upper_bound = first_frame_offset + seek_table->points[i].stream_offset;
			new_upper_bound_sample = seek_table->points[i].sample_number;
		}
		/* final protection against unsorted seek tables; keep original values if bogus */
		if(new_upper_bound >= new_lower_bound) {
			lower_bound = new_lower_bound;
			upper_bound = new_upper_bound;
			lower_bound_sample = new_lower_bound_sample;
			upper_bound_sample = new_upper_bound_sample;
		}
	}

	FLAC__ASSERT(upper_bound_sample >= lower_bound_sample);
	/* there are 2 insidious ways that the following equality occurs, which
	 * we need to fix:
	 *  1) total_samples is 0 (unknown) and target_sample is 0
	 *  2) total_samples is 0 (unknown) and target_sample happens to be
	 *     exactly equal to the last seek point in the seek table; this
	 *     means there is no seek point above it, and upper_bound_samples
	 *     remains equal to the estimate (of target_samples) we made above
	 * in either case it does not hurt to move upper_bound_sample up by 1
	 */
	if(upper_bound_sample == lower_bound_sample)
		upper_bound_sample++;

	decoder->private_->target_sample = target_sample;
	while(1) {
		/* check if the bounds are still ok */
		if (lower_bound_sample >= upper_bound_sample || lower_bound > upper_bound) {
			decoder->protected_->state = FLAC__STREAM_DECODER_SEEK_ERROR;
			return false;
		}
#ifndef FLAC__INTEGER_ONLY_LIBRARY
		pos = (FLAC__int64)lower_bound + (FLAC__int64)((double)(target_sample - lower_bound_sample) / (double)(upper_bound_sample - lower_bound_sample) * (double)(upper_bound - lower_bound)) - approx_bytes_per_frame;
#else
		/* a little less accurate: */
		if(upper_bound - lower_bound < 0xffffffff)
			pos = (FLAC__int64)lower_bound + (FLAC__int64)(((target_sample - lower_bound_sample) * (upper_bound - lower_bound)) / (upper_bound_sample - lower_bound_sample)) - approx_bytes_per_frame;
		else /* @@@ WATCHOUT, ~2TB limit */
			pos = (FLAC__int64)lower_bound + (FLAC__int64)((((target_sample - lower_bound_sample)>>8) * ((upper_bound - lower_bound)>>8)) / ((upper_bound_sample - lower_bound_sample)>>16)) - approx_bytes_per_frame;
#endif
		if(pos >= (FLAC__int64)upper_bound)
			pos = (FLAC__int64)upper_bound - 1;
		if(pos < (FLAC__int64)lower_bound)
			pos = (FLAC__int64)lower_bound;
		if(decoder->private_->seek_callback(decoder, (FLAC__uint64)pos, decoder->private_->client_data) != FLAC__STREAM_DECODER_SEEK_STATUS_OK) {
			decoder->protected_->state = FLAC__STREAM_DECODER_SEEK_ERROR;
			return false;
		}
		if(!FLAC__stream_decoder_flush(decoder)) {
			/* above call sets the state for us */
			return false;
		}
		/* Now we need to get a frame.  First we need to reset our
		 * unparseable_frame_count; if we get too many unparseable
		 * frames in a row, the read callback will return
		 * FLAC__STREAM_DECODER_READ_STATUS_ABORT, causing
		 * FLAC__stream_decoder_process_single() to return false.
		 */
		decoder->private_->unparseable_frame_count = 0;
		if(!FLAC__stream_decoder_process_single(decoder) ||
		   decoder->protected_->state == FLAC__STREAM_DECODER_ABORTED) {
			decoder->protected_->state = FLAC__STREAM_DECODER_SEEK_ERROR;
			return false;
		}
		/* our write callback will change the state when it gets to the target frame */
		/* actually, we could have got_a_frame if our decoder is at FLAC__STREAM_DECODER_END_OF_STREAM so we need to check for that also */
#if 0
		/*@@@@@@ used to be the following; not clear if the check for end of stream is needed anymore */
		if(decoder->protected_->state != FLAC__SEEKABLE_STREAM_DECODER_SEEKING && decoder->protected_->state != FLAC__STREAM_DECODER_END_OF_STREAM)
			break;
#endif
		if(!decoder->private_->is_seeking)
			break;

		FLAC__ASSERT(decoder->private_->last_frame.header.number_type == FLAC__FRAME_NUMBER_TYPE_SAMPLE_NUMBER);
		this_frame_sample = decoder->private_->last_frame.header.number.sample_number;

		if (0 == decoder->private_->samples_decoded || (this_frame_sample + decoder->private_->last_frame.header.blocksize >= upper_bound_sample && !first_seek)) {
			if (pos == (FLAC__int64)lower_bound) {
				/* can't move back any more than the first frame, something is fatally wrong */
				decoder->protected_->state = FLAC__STREAM_DECODER_SEEK_ERROR;
				return false;
			}
			/* our last move backwards wasn't big enough, try again */
			approx_bytes_per_frame = approx_bytes_per_frame? approx_bytes_per_frame * 2 : 16;
			continue;
		}
		/* allow one seek over upper bound, so we can get a correct upper_bound_sample for streams with unknown total_samples */
		first_seek = false;

		/* make sure we are not seeking in corrupted stream */
		if (this_frame_sample < lower_bound_sample) {
			decoder->protected_->state = FLAC__STREAM_DECODER_SEEK_ERROR;
			return false;
		}

		/* we need to narrow the search */
		if(target_sample < this_frame_sample) {
			upper_bound_sample = this_frame_sample + decoder->private_->last_frame.header.blocksize;
/*@@@@@@ what will decode position be if at end of stream? */
			if(!FLAC__stream_decoder_get_decode_position(decoder, &upper_bound)) {
				decoder->protected_->state = FLAC__STREAM_DECODER_SEEK_ERROR;
				return false;
			}
			approx_bytes_per_frame = (unsigned)(2 * (upper_bound - pos) / 3 + 16);
		}
		else { /* target_sample >= this_frame_sample + this frame's blocksize */
			lower_bound_sample = this_frame_sample + decoder->private_->last_frame.header.blocksize;
			if(!FLAC__stream_decoder_get_decode_position(decoder, &lower_bound)) {
				decoder->protected_->state = FLAC__STREAM_DECODER_SEEK_ERROR;
				return false;
			}
			approx_bytes_per_frame = (unsigned)(2 * (lower_bound - pos) / 3 + 16);
		}
	}

	return true;
}