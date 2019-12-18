#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_5__* private_; TYPE_1__* protected_; } ;
struct TYPE_15__ {size_t frame_samples; void* stream_offset; void* sample_number; } ;
struct TYPE_11__ {unsigned int num_points; TYPE_6__* points; } ;
struct TYPE_12__ {TYPE_2__ seek_table; } ;
struct TYPE_13__ {int is_last; unsigned int length; TYPE_3__ data; int /*<<< orphan*/  type; } ;
struct TYPE_14__ {int /*<<< orphan*/  input; TYPE_4__ seek_table; } ;
struct TYPE_10__ {int /*<<< orphan*/  state; } ;
typedef  void* FLAC__uint64 ;
typedef  size_t FLAC__uint32 ;
typedef  int FLAC__bool ;
typedef  TYPE_6__ FLAC__StreamMetadata_SeekPoint ;
typedef  TYPE_7__ FLAC__StreamDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC__ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLAC__METADATA_TYPE_SEEKTABLE ; 
 int /*<<< orphan*/  FLAC__STREAM_DECODER_MEMORY_ALLOCATION_ERROR ; 
 int /*<<< orphan*/  FLAC__STREAM_METADATA_SEEKPOINT_FRAME_SAMPLES_LEN ; 
 unsigned int FLAC__STREAM_METADATA_SEEKPOINT_LENGTH ; 
 int /*<<< orphan*/  FLAC__STREAM_METADATA_SEEKPOINT_SAMPLE_NUMBER_LEN ; 
 int /*<<< orphan*/  FLAC__STREAM_METADATA_SEEKPOINT_STREAM_OFFSET_LEN ; 
 int /*<<< orphan*/  FLAC__bitreader_is_consumed_byte_aligned (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLAC__bitreader_read_raw_uint32 (int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLAC__bitreader_read_raw_uint64 (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLAC__bitreader_skip_byte_block_aligned_no_crc (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ safe_realloc_mul_2op_ (TYPE_6__*,unsigned int,int) ; 

FLAC__bool read_metadata_seektable_(FLAC__StreamDecoder *decoder, FLAC__bool is_last, unsigned length)
{
	FLAC__uint32 i, x;
	FLAC__uint64 xx;

	FLAC__ASSERT(FLAC__bitreader_is_consumed_byte_aligned(decoder->private_->input));

	decoder->private_->seek_table.type = FLAC__METADATA_TYPE_SEEKTABLE;
	decoder->private_->seek_table.is_last = is_last;
	decoder->private_->seek_table.length = length;

	decoder->private_->seek_table.data.seek_table.num_points = length / FLAC__STREAM_METADATA_SEEKPOINT_LENGTH;

	/* use realloc since we may pass through here several times (e.g. after seeking) */
	if(0 == (decoder->private_->seek_table.data.seek_table.points = (FLAC__StreamMetadata_SeekPoint*)safe_realloc_mul_2op_(decoder->private_->seek_table.data.seek_table.points, decoder->private_->seek_table.data.seek_table.num_points, /*times*/sizeof(FLAC__StreamMetadata_SeekPoint)))) {
		decoder->protected_->state = FLAC__STREAM_DECODER_MEMORY_ALLOCATION_ERROR;
		return false;
	}
	for(i = 0; i < decoder->private_->seek_table.data.seek_table.num_points; i++) {
		if(!FLAC__bitreader_read_raw_uint64(decoder->private_->input, &xx, FLAC__STREAM_METADATA_SEEKPOINT_SAMPLE_NUMBER_LEN))
			return false; /* read_callback_ sets the state for us */
		decoder->private_->seek_table.data.seek_table.points[i].sample_number = xx;

		if(!FLAC__bitreader_read_raw_uint64(decoder->private_->input, &xx, FLAC__STREAM_METADATA_SEEKPOINT_STREAM_OFFSET_LEN))
			return false; /* read_callback_ sets the state for us */
		decoder->private_->seek_table.data.seek_table.points[i].stream_offset = xx;

		if(!FLAC__bitreader_read_raw_uint32(decoder->private_->input, &x, FLAC__STREAM_METADATA_SEEKPOINT_FRAME_SAMPLES_LEN))
			return false; /* read_callback_ sets the state for us */
		decoder->private_->seek_table.data.seek_table.points[i].frame_samples = x;
	}
	length -= (decoder->private_->seek_table.data.seek_table.num_points * FLAC__STREAM_METADATA_SEEKPOINT_LENGTH);
	/* if there is a partial point left, skip over it */
	if(length > 0) {
		/*@@@ do a send_error_to_client_() here?  there's an argument for either way */
		if(!FLAC__bitreader_skip_byte_block_aligned_no_crc(decoder->private_->input, length))
			return false; /* read_callback_ sets the state for us */
	}

	return true;
}