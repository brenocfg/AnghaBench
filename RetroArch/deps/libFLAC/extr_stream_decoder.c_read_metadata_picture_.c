#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* private_; TYPE_1__* protected_; } ;
struct TYPE_9__ {char* mime_type; char* description; size_t width; size_t height; size_t depth; size_t colors; size_t data_length; char* data; scalar_t__ type; } ;
struct TYPE_8__ {int /*<<< orphan*/  input; } ;
struct TYPE_7__ {void* state; } ;
typedef  size_t FLAC__uint32 ;
typedef  char FLAC__byte ;
typedef  int FLAC__bool ;
typedef  scalar_t__ FLAC__StreamMetadata_Picture_Type ;
typedef  TYPE_3__ FLAC__StreamMetadata_Picture ;
typedef  TYPE_4__ FLAC__StreamDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC__ASSERT (int /*<<< orphan*/ ) ; 
 void* FLAC__STREAM_DECODER_MEMORY_ALLOCATION_ERROR ; 
 int /*<<< orphan*/  FLAC__STREAM_METADATA_PICTURE_COLORS_LEN ; 
 int /*<<< orphan*/  FLAC__STREAM_METADATA_PICTURE_DATA_LENGTH_LEN ; 
 int /*<<< orphan*/  FLAC__STREAM_METADATA_PICTURE_DEPTH_LEN ; 
 int /*<<< orphan*/  FLAC__STREAM_METADATA_PICTURE_DESCRIPTION_LENGTH_LEN ; 
 int /*<<< orphan*/  FLAC__STREAM_METADATA_PICTURE_HEIGHT_LEN ; 
 int /*<<< orphan*/  FLAC__STREAM_METADATA_PICTURE_MIME_TYPE_LENGTH_LEN ; 
 int /*<<< orphan*/  FLAC__STREAM_METADATA_PICTURE_TYPE_LEN ; 
 int /*<<< orphan*/  FLAC__STREAM_METADATA_PICTURE_WIDTH_LEN ; 
 int /*<<< orphan*/  FLAC__bitreader_is_consumed_byte_aligned (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLAC__bitreader_read_byte_block_aligned_no_crc (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  FLAC__bitreader_read_raw_uint32 (int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ safe_malloc_ (size_t) ; 
 scalar_t__ safe_malloc_add_2op_ (size_t,int) ; 

FLAC__bool read_metadata_picture_(FLAC__StreamDecoder *decoder, FLAC__StreamMetadata_Picture *obj)
{
	FLAC__uint32 x;

	FLAC__ASSERT(FLAC__bitreader_is_consumed_byte_aligned(decoder->private_->input));

	/* read type */
	if(!FLAC__bitreader_read_raw_uint32(decoder->private_->input, &x, FLAC__STREAM_METADATA_PICTURE_TYPE_LEN))
		return false; /* read_callback_ sets the state for us */
	obj->type = (FLAC__StreamMetadata_Picture_Type)x;

	/* read MIME type */
	if(!FLAC__bitreader_read_raw_uint32(decoder->private_->input, &x, FLAC__STREAM_METADATA_PICTURE_MIME_TYPE_LENGTH_LEN))
		return false; /* read_callback_ sets the state for us */
	if(0 == (obj->mime_type = (char*)safe_malloc_add_2op_(x, /*+*/1))) {
		decoder->protected_->state = FLAC__STREAM_DECODER_MEMORY_ALLOCATION_ERROR;
		return false;
	}
	if(x > 0) {
		if(!FLAC__bitreader_read_byte_block_aligned_no_crc(decoder->private_->input, (FLAC__byte*)obj->mime_type, x))
			return false; /* read_callback_ sets the state for us */
	}
	obj->mime_type[x] = '\0';

	/* read description */
	if(!FLAC__bitreader_read_raw_uint32(decoder->private_->input, &x, FLAC__STREAM_METADATA_PICTURE_DESCRIPTION_LENGTH_LEN))
		return false; /* read_callback_ sets the state for us */
	if(0 == (obj->description = (FLAC__byte*)safe_malloc_add_2op_(x, /*+*/1))) {
		decoder->protected_->state = FLAC__STREAM_DECODER_MEMORY_ALLOCATION_ERROR;
		return false;
	}
	if(x > 0) {
		if(!FLAC__bitreader_read_byte_block_aligned_no_crc(decoder->private_->input, obj->description, x))
			return false; /* read_callback_ sets the state for us */
	}
	obj->description[x] = '\0';

	/* read width */
	if(!FLAC__bitreader_read_raw_uint32(decoder->private_->input, &obj->width, FLAC__STREAM_METADATA_PICTURE_WIDTH_LEN))
		return false; /* read_callback_ sets the state for us */

	/* read height */
	if(!FLAC__bitreader_read_raw_uint32(decoder->private_->input, &obj->height, FLAC__STREAM_METADATA_PICTURE_HEIGHT_LEN))
		return false; /* read_callback_ sets the state for us */

	/* read depth */
	if(!FLAC__bitreader_read_raw_uint32(decoder->private_->input, &obj->depth, FLAC__STREAM_METADATA_PICTURE_DEPTH_LEN))
		return false; /* read_callback_ sets the state for us */

	/* read colors */
	if(!FLAC__bitreader_read_raw_uint32(decoder->private_->input, &obj->colors, FLAC__STREAM_METADATA_PICTURE_COLORS_LEN))
		return false; /* read_callback_ sets the state for us */

	/* read data */
	if(!FLAC__bitreader_read_raw_uint32(decoder->private_->input, &(obj->data_length), FLAC__STREAM_METADATA_PICTURE_DATA_LENGTH_LEN))
		return false; /* read_callback_ sets the state for us */
	if(0 == (obj->data = (FLAC__byte*)safe_malloc_(obj->data_length))) {
		decoder->protected_->state = FLAC__STREAM_DECODER_MEMORY_ALLOCATION_ERROR;
		return false;
	}
	if(obj->data_length > 0) {
		if(!FLAC__bitreader_read_byte_block_aligned_no_crc(decoder->private_->input, obj->data, obj->data_length))
			return false; /* read_callback_ sets the state for us */
	}

	return true;
}