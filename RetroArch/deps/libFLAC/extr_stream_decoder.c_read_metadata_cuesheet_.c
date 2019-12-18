#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_2__* private_; TYPE_1__* protected_; } ;
struct TYPE_14__ {int is_cd; size_t num_tracks; TYPE_3__* tracks; int /*<<< orphan*/  lead_in; scalar_t__ media_catalog_number; } ;
struct TYPE_13__ {void* number; int /*<<< orphan*/  offset; } ;
struct TYPE_12__ {size_t type; size_t pre_emphasis; scalar_t__ num_indices; TYPE_4__* indices; scalar_t__ isrc; void* number; int /*<<< orphan*/  offset; } ;
struct TYPE_11__ {int /*<<< orphan*/  input; } ;
struct TYPE_10__ {void* state; } ;
typedef  size_t FLAC__uint32 ;
typedef  void* FLAC__byte ;
typedef  int FLAC__bool ;
typedef  TYPE_3__ FLAC__StreamMetadata_CueSheet_Track ;
typedef  TYPE_4__ FLAC__StreamMetadata_CueSheet_Index ;
typedef  TYPE_5__ FLAC__StreamMetadata_CueSheet ;
typedef  TYPE_6__ FLAC__StreamDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC__ASSERT (int) ; 
 void* FLAC__STREAM_DECODER_MEMORY_ALLOCATION_ERROR ; 
 int /*<<< orphan*/  FLAC__STREAM_METADATA_CUESHEET_INDEX_NUMBER_LEN ; 
 int /*<<< orphan*/  FLAC__STREAM_METADATA_CUESHEET_INDEX_OFFSET_LEN ; 
 int /*<<< orphan*/  FLAC__STREAM_METADATA_CUESHEET_INDEX_RESERVED_LEN ; 
 int /*<<< orphan*/  FLAC__STREAM_METADATA_CUESHEET_IS_CD_LEN ; 
 int /*<<< orphan*/  FLAC__STREAM_METADATA_CUESHEET_LEAD_IN_LEN ; 
 int FLAC__STREAM_METADATA_CUESHEET_MEDIA_CATALOG_NUMBER_LEN ; 
 int /*<<< orphan*/  FLAC__STREAM_METADATA_CUESHEET_NUM_TRACKS_LEN ; 
 int /*<<< orphan*/  FLAC__STREAM_METADATA_CUESHEET_RESERVED_LEN ; 
 int FLAC__STREAM_METADATA_CUESHEET_TRACK_ISRC_LEN ; 
 int /*<<< orphan*/  FLAC__STREAM_METADATA_CUESHEET_TRACK_NUMBER_LEN ; 
 int /*<<< orphan*/  FLAC__STREAM_METADATA_CUESHEET_TRACK_NUM_INDICES_LEN ; 
 int /*<<< orphan*/  FLAC__STREAM_METADATA_CUESHEET_TRACK_OFFSET_LEN ; 
 int /*<<< orphan*/  FLAC__STREAM_METADATA_CUESHEET_TRACK_PRE_EMPHASIS_LEN ; 
 int /*<<< orphan*/  FLAC__STREAM_METADATA_CUESHEET_TRACK_RESERVED_LEN ; 
 int /*<<< orphan*/  FLAC__STREAM_METADATA_CUESHEET_TRACK_TYPE_LEN ; 
 int FLAC__bitreader_is_consumed_byte_aligned (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLAC__bitreader_read_byte_block_aligned_no_crc (int /*<<< orphan*/ ,void**,int) ; 
 int /*<<< orphan*/  FLAC__bitreader_read_raw_uint32 (int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLAC__bitreader_read_raw_uint64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLAC__bitreader_skip_bits_no_crc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ safe_calloc_ (scalar_t__,int) ; 

FLAC__bool read_metadata_cuesheet_(FLAC__StreamDecoder *decoder, FLAC__StreamMetadata_CueSheet *obj)
{
	FLAC__uint32 i, j, x;

	FLAC__ASSERT(FLAC__bitreader_is_consumed_byte_aligned(decoder->private_->input));

	memset(obj, 0, sizeof(FLAC__StreamMetadata_CueSheet));

	FLAC__ASSERT(FLAC__STREAM_METADATA_CUESHEET_MEDIA_CATALOG_NUMBER_LEN % 8 == 0);
	if(!FLAC__bitreader_read_byte_block_aligned_no_crc(decoder->private_->input, (FLAC__byte*)obj->media_catalog_number, FLAC__STREAM_METADATA_CUESHEET_MEDIA_CATALOG_NUMBER_LEN/8))
		return false; /* read_callback_ sets the state for us */

	if(!FLAC__bitreader_read_raw_uint64(decoder->private_->input, &obj->lead_in, FLAC__STREAM_METADATA_CUESHEET_LEAD_IN_LEN))
		return false; /* read_callback_ sets the state for us */

	if(!FLAC__bitreader_read_raw_uint32(decoder->private_->input, &x, FLAC__STREAM_METADATA_CUESHEET_IS_CD_LEN))
		return false; /* read_callback_ sets the state for us */
	obj->is_cd = x? true : false;

	if(!FLAC__bitreader_skip_bits_no_crc(decoder->private_->input, FLAC__STREAM_METADATA_CUESHEET_RESERVED_LEN))
		return false; /* read_callback_ sets the state for us */

	if(!FLAC__bitreader_read_raw_uint32(decoder->private_->input, &x, FLAC__STREAM_METADATA_CUESHEET_NUM_TRACKS_LEN))
		return false; /* read_callback_ sets the state for us */
	obj->num_tracks = x;

	if(obj->num_tracks > 0) {
		if(0 == (obj->tracks = (FLAC__StreamMetadata_CueSheet_Track*)safe_calloc_(obj->num_tracks, sizeof(FLAC__StreamMetadata_CueSheet_Track)))) {
			decoder->protected_->state = FLAC__STREAM_DECODER_MEMORY_ALLOCATION_ERROR;
			return false;
		}
		for(i = 0; i < obj->num_tracks; i++) {
			FLAC__StreamMetadata_CueSheet_Track *track = &obj->tracks[i];
			if(!FLAC__bitreader_read_raw_uint64(decoder->private_->input, &track->offset, FLAC__STREAM_METADATA_CUESHEET_TRACK_OFFSET_LEN))
				return false; /* read_callback_ sets the state for us */

			if(!FLAC__bitreader_read_raw_uint32(decoder->private_->input, &x, FLAC__STREAM_METADATA_CUESHEET_TRACK_NUMBER_LEN))
				return false; /* read_callback_ sets the state for us */
			track->number = (FLAC__byte)x;

			FLAC__ASSERT(FLAC__STREAM_METADATA_CUESHEET_TRACK_ISRC_LEN % 8 == 0);
			if(!FLAC__bitreader_read_byte_block_aligned_no_crc(decoder->private_->input, (FLAC__byte*)track->isrc, FLAC__STREAM_METADATA_CUESHEET_TRACK_ISRC_LEN/8))
				return false; /* read_callback_ sets the state for us */

			if(!FLAC__bitreader_read_raw_uint32(decoder->private_->input, &x, FLAC__STREAM_METADATA_CUESHEET_TRACK_TYPE_LEN))
				return false; /* read_callback_ sets the state for us */
			track->type = x;

			if(!FLAC__bitreader_read_raw_uint32(decoder->private_->input, &x, FLAC__STREAM_METADATA_CUESHEET_TRACK_PRE_EMPHASIS_LEN))
				return false; /* read_callback_ sets the state for us */
			track->pre_emphasis = x;

			if(!FLAC__bitreader_skip_bits_no_crc(decoder->private_->input, FLAC__STREAM_METADATA_CUESHEET_TRACK_RESERVED_LEN))
				return false; /* read_callback_ sets the state for us */

			if(!FLAC__bitreader_read_raw_uint32(decoder->private_->input, &x, FLAC__STREAM_METADATA_CUESHEET_TRACK_NUM_INDICES_LEN))
				return false; /* read_callback_ sets the state for us */
			track->num_indices = (FLAC__byte)x;

			if(track->num_indices > 0) {
				if(0 == (track->indices = (FLAC__StreamMetadata_CueSheet_Index*)safe_calloc_(track->num_indices, sizeof(FLAC__StreamMetadata_CueSheet_Index)))) {
					decoder->protected_->state = FLAC__STREAM_DECODER_MEMORY_ALLOCATION_ERROR;
					return false;
				}
				for(j = 0; j < track->num_indices; j++) {
					FLAC__StreamMetadata_CueSheet_Index *indx = &track->indices[j];
					if(!FLAC__bitreader_read_raw_uint64(decoder->private_->input, &indx->offset, FLAC__STREAM_METADATA_CUESHEET_INDEX_OFFSET_LEN))
						return false; /* read_callback_ sets the state for us */

					if(!FLAC__bitreader_read_raw_uint32(decoder->private_->input, &x, FLAC__STREAM_METADATA_CUESHEET_INDEX_NUMBER_LEN))
						return false; /* read_callback_ sets the state for us */
					indx->number = (FLAC__byte)x;

					if(!FLAC__bitreader_skip_bits_no_crc(decoder->private_->input, FLAC__STREAM_METADATA_CUESHEET_INDEX_RESERVED_LEN))
						return false; /* read_callback_ sets the state for us */
				}
			}
		}
	}

	return true;
}