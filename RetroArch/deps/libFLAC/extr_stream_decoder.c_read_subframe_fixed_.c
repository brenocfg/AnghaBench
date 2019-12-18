#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_23__ {int blocksize; } ;
struct TYPE_24__ {TYPE_7__ header; TYPE_2__* subframes; } ;
struct TYPE_25__ {scalar_t__* output; TYPE_8__ frame; int /*<<< orphan*/ * residual; int /*<<< orphan*/ * partitioned_rice_contents; int /*<<< orphan*/  input; } ;
struct TYPE_20__ {unsigned int order; int /*<<< orphan*/ * contents; } ;
struct TYPE_21__ {TYPE_4__ partitioned_rice; } ;
struct TYPE_22__ {int type; TYPE_5__ data; } ;
struct TYPE_19__ {void* state; } ;
struct TYPE_15__ {unsigned int order; int /*<<< orphan*/ * warmup; TYPE_6__ entropy_coding_method; int /*<<< orphan*/  residual; } ;
struct TYPE_17__ {TYPE_10__ fixed; } ;
struct TYPE_18__ {int /*<<< orphan*/  type; TYPE_1__ data; } ;
struct TYPE_16__ {TYPE_9__* private_; TYPE_3__* protected_; } ;
typedef  unsigned int const FLAC__uint32 ;
typedef  int /*<<< orphan*/  FLAC__int32 ;
typedef  int FLAC__bool ;
typedef  TYPE_10__ FLAC__Subframe_Fixed ;
typedef  TYPE_11__ FLAC__StreamDecoder ;
typedef  int FLAC__EntropyCodingMethodType ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC__ASSERT (int /*<<< orphan*/ ) ; 
#define  FLAC__ENTROPY_CODING_METHOD_PARTITIONED_RICE 129 
#define  FLAC__ENTROPY_CODING_METHOD_PARTITIONED_RICE2 128 
 int /*<<< orphan*/  FLAC__ENTROPY_CODING_METHOD_PARTITIONED_RICE_ORDER_LEN ; 
 int /*<<< orphan*/  FLAC__ENTROPY_CODING_METHOD_TYPE_LEN ; 
 int /*<<< orphan*/  FLAC__STREAM_DECODER_ERROR_STATUS_LOST_SYNC ; 
 int /*<<< orphan*/  FLAC__STREAM_DECODER_ERROR_STATUS_UNPARSEABLE_STREAM ; 
 void* FLAC__STREAM_DECODER_SEARCH_FOR_FRAME_SYNC ; 
 int /*<<< orphan*/  FLAC__SUBFRAME_TYPE_FIXED ; 
 int /*<<< orphan*/  FLAC__bitreader_read_raw_int32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  FLAC__bitreader_read_raw_uint32 (int /*<<< orphan*/ ,unsigned int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLAC__fixed_restore_signal (int /*<<< orphan*/ ,int,unsigned int const,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  read_residual_partitioned_rice_ (TYPE_11__*,unsigned int const,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  send_error_to_client_ (TYPE_11__*,int /*<<< orphan*/ ) ; 

FLAC__bool read_subframe_fixed_(FLAC__StreamDecoder *decoder, unsigned channel, unsigned bps, const unsigned order, FLAC__bool do_full_decode)
{
	FLAC__Subframe_Fixed *subframe = &decoder->private_->frame.subframes[channel].data.fixed;
	FLAC__int32 i32;
	FLAC__uint32 u32;
	unsigned u;

	decoder->private_->frame.subframes[channel].type = FLAC__SUBFRAME_TYPE_FIXED;

	subframe->residual = decoder->private_->residual[channel];
	subframe->order = order;

	/* read warm-up samples */
	for(u = 0; u < order; u++) {
		if(!FLAC__bitreader_read_raw_int32(decoder->private_->input, &i32, bps))
			return false; /* read_callback_ sets the state for us */
		subframe->warmup[u] = i32;
	}

	/* read entropy coding method info */
	if(!FLAC__bitreader_read_raw_uint32(decoder->private_->input, &u32, FLAC__ENTROPY_CODING_METHOD_TYPE_LEN))
		return false; /* read_callback_ sets the state for us */
	subframe->entropy_coding_method.type = (FLAC__EntropyCodingMethodType)u32;
	switch(subframe->entropy_coding_method.type) {
		case FLAC__ENTROPY_CODING_METHOD_PARTITIONED_RICE:
		case FLAC__ENTROPY_CODING_METHOD_PARTITIONED_RICE2:
			if(!FLAC__bitreader_read_raw_uint32(decoder->private_->input, &u32, FLAC__ENTROPY_CODING_METHOD_PARTITIONED_RICE_ORDER_LEN))
				return false; /* read_callback_ sets the state for us */
			if(decoder->private_->frame.header.blocksize >> u32 < order) {
				send_error_to_client_(decoder, FLAC__STREAM_DECODER_ERROR_STATUS_LOST_SYNC);
				decoder->protected_->state = FLAC__STREAM_DECODER_SEARCH_FOR_FRAME_SYNC;
				return true;
			}
			subframe->entropy_coding_method.data.partitioned_rice.order = u32;
			subframe->entropy_coding_method.data.partitioned_rice.contents = &decoder->private_->partitioned_rice_contents[channel];
			break;
		default:
			send_error_to_client_(decoder, FLAC__STREAM_DECODER_ERROR_STATUS_UNPARSEABLE_STREAM);
			decoder->protected_->state = FLAC__STREAM_DECODER_SEARCH_FOR_FRAME_SYNC;
			return true;
	}

	/* read residual */
	switch(subframe->entropy_coding_method.type) {
		case FLAC__ENTROPY_CODING_METHOD_PARTITIONED_RICE:
		case FLAC__ENTROPY_CODING_METHOD_PARTITIONED_RICE2:
			if(!read_residual_partitioned_rice_(decoder, order, subframe->entropy_coding_method.data.partitioned_rice.order, &decoder->private_->partitioned_rice_contents[channel], decoder->private_->residual[channel], /*is_extended=*/subframe->entropy_coding_method.type == FLAC__ENTROPY_CODING_METHOD_PARTITIONED_RICE2))
				return false;
			break;
		default:
			FLAC__ASSERT(0);
	}

	/* decode the subframe */
	if(do_full_decode) {
		memcpy(decoder->private_->output[channel], subframe->warmup, sizeof(FLAC__int32) * order);
		FLAC__fixed_restore_signal(decoder->private_->residual[channel], decoder->private_->frame.header.blocksize-order, order, decoder->private_->output[channel]+order);
	}

	return true;
}