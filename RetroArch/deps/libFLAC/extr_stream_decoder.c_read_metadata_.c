#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_44__   TYPE_9__ ;
typedef  struct TYPE_43__   TYPE_8__ ;
typedef  struct TYPE_42__   TYPE_7__ ;
typedef  struct TYPE_41__   TYPE_6__ ;
typedef  struct TYPE_40__   TYPE_5__ ;
typedef  struct TYPE_39__   TYPE_4__ ;
typedef  struct TYPE_38__   TYPE_3__ ;
typedef  struct TYPE_37__   TYPE_2__ ;
typedef  struct TYPE_36__   TYPE_24__ ;
typedef  struct TYPE_35__   TYPE_22__ ;
typedef  struct TYPE_34__   TYPE_1__ ;
typedef  struct TYPE_33__   TYPE_18__ ;
typedef  struct TYPE_32__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  block ;
struct TYPE_38__ {TYPE_8__* data; } ;
struct TYPE_35__ {TYPE_8__* data; TYPE_8__* description; TYPE_8__* mime_type; } ;
struct TYPE_36__ {size_t num_tracks; TYPE_8__* tracks; } ;
struct TYPE_37__ {TYPE_8__* entry; } ;
struct TYPE_33__ {size_t num_comments; TYPE_8__* comments; TYPE_2__ vendor_string; } ;
struct TYPE_34__ {TYPE_8__* data; TYPE_8__* id; } ;
struct TYPE_40__ {int /*<<< orphan*/  md5sum; } ;
struct TYPE_41__ {TYPE_3__ unknown; TYPE_22__ picture; TYPE_24__ cue_sheet; TYPE_18__ vorbis_comment; TYPE_1__ application; TYPE_5__ stream_info; } ;
struct TYPE_44__ {int is_last; size_t length; TYPE_6__ data; scalar_t__ type; } ;
struct TYPE_43__ {struct TYPE_43__* indices; struct TYPE_43__* entry; } ;
struct TYPE_42__ {int has_stream_info; int do_md5_checking; int has_seek_table; scalar_t__ metadata_filter_ids_count; scalar_t__ first_frame_offset; int /*<<< orphan*/  client_data; int /*<<< orphan*/  (* metadata_callback ) (TYPE_10__*,TYPE_9__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  is_seeking; int /*<<< orphan*/  input; scalar_t__* metadata_filter; TYPE_9__ seek_table; TYPE_9__ stream_info; } ;
struct TYPE_39__ {void* state; } ;
struct TYPE_32__ {TYPE_4__* protected_; TYPE_7__* private_; } ;
typedef  size_t FLAC__uint32 ;
typedef  TYPE_8__ FLAC__byte ;
typedef  int FLAC__bool ;
typedef  TYPE_9__ FLAC__StreamMetadata ;
typedef  TYPE_10__ FLAC__StreamDecoder ;
typedef  scalar_t__ FLAC__MetadataType ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC__ASSERT (int /*<<< orphan*/ ) ; 
#define  FLAC__METADATA_TYPE_APPLICATION 134 
#define  FLAC__METADATA_TYPE_CUESHEET 133 
#define  FLAC__METADATA_TYPE_PADDING 132 
#define  FLAC__METADATA_TYPE_PICTURE 131 
#define  FLAC__METADATA_TYPE_SEEKTABLE 130 
#define  FLAC__METADATA_TYPE_STREAMINFO 129 
#define  FLAC__METADATA_TYPE_VORBIS_COMMENT 128 
 void* FLAC__STREAM_DECODER_MEMORY_ALLOCATION_ERROR ; 
 void* FLAC__STREAM_DECODER_SEARCH_FOR_FRAME_SYNC ; 
 int FLAC__STREAM_METADATA_APPLICATION_ID_LEN ; 
 int /*<<< orphan*/  FLAC__STREAM_METADATA_IS_LAST_LEN ; 
 int /*<<< orphan*/  FLAC__STREAM_METADATA_LENGTH_LEN ; 
 int /*<<< orphan*/  FLAC__STREAM_METADATA_TYPE_LEN ; 
 int /*<<< orphan*/  FLAC__bitreader_is_consumed_byte_aligned (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLAC__bitreader_read_byte_block_aligned_no_crc (int /*<<< orphan*/ ,TYPE_8__*,unsigned int) ; 
 int /*<<< orphan*/  FLAC__bitreader_read_raw_uint32 (int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLAC__bitreader_skip_byte_block_aligned_no_crc (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  FLAC__stream_decoder_get_decode_position (TYPE_10__*,scalar_t__*) ; 
 int /*<<< orphan*/  free (TYPE_8__*) ; 
 scalar_t__ has_id_filtered_ (TYPE_10__*,TYPE_8__*) ; 
 scalar_t__ malloc (unsigned int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_metadata_cuesheet_ (TYPE_10__*,TYPE_24__*) ; 
 int /*<<< orphan*/  read_metadata_picture_ (TYPE_10__*,TYPE_22__*) ; 
 int /*<<< orphan*/  read_metadata_seektable_ (TYPE_10__*,int,size_t) ; 
 int /*<<< orphan*/  read_metadata_streaminfo_ (TYPE_10__*,int,size_t) ; 
 int /*<<< orphan*/  read_metadata_vorbiscomment_ (TYPE_10__*,TYPE_18__*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (TYPE_10__*,TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_10__*,TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_10__*,TYPE_9__*,int /*<<< orphan*/ ) ; 

FLAC__bool read_metadata_(FLAC__StreamDecoder *decoder)
{
	FLAC__bool is_last;
	FLAC__uint32 i, x, type, length;

	FLAC__ASSERT(FLAC__bitreader_is_consumed_byte_aligned(decoder->private_->input));

	if(!FLAC__bitreader_read_raw_uint32(decoder->private_->input, &x, FLAC__STREAM_METADATA_IS_LAST_LEN))
		return false; /* read_callback_ sets the state for us */
	is_last = x? true : false;

	if(!FLAC__bitreader_read_raw_uint32(decoder->private_->input, &type, FLAC__STREAM_METADATA_TYPE_LEN))
		return false; /* read_callback_ sets the state for us */

	if(!FLAC__bitreader_read_raw_uint32(decoder->private_->input, &length, FLAC__STREAM_METADATA_LENGTH_LEN))
		return false; /* read_callback_ sets the state for us */

	if(type == FLAC__METADATA_TYPE_STREAMINFO) {
		if(!read_metadata_streaminfo_(decoder, is_last, length))
			return false;

		decoder->private_->has_stream_info = true;
		if(0 == memcmp(decoder->private_->stream_info.data.stream_info.md5sum, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 16))
			decoder->private_->do_md5_checking = false;
		if(!decoder->private_->is_seeking && decoder->private_->metadata_filter[FLAC__METADATA_TYPE_STREAMINFO] && decoder->private_->metadata_callback)
			decoder->private_->metadata_callback(decoder, &decoder->private_->stream_info, decoder->private_->client_data);
	}
	else if(type == FLAC__METADATA_TYPE_SEEKTABLE) {
		/* just in case we already have a seek table, and reading the next one fails: */
		decoder->private_->has_seek_table = false;

		if(!read_metadata_seektable_(decoder, is_last, length))
			return false;

		decoder->private_->has_seek_table = true;
		if(!decoder->private_->is_seeking && decoder->private_->metadata_filter[FLAC__METADATA_TYPE_SEEKTABLE] && decoder->private_->metadata_callback)
			decoder->private_->metadata_callback(decoder, &decoder->private_->seek_table, decoder->private_->client_data);
	}
	else {
		FLAC__bool skip_it = !decoder->private_->metadata_filter[type];
		unsigned real_length = length;
		FLAC__StreamMetadata block;

		memset(&block, 0, sizeof(block));
		block.is_last = is_last;
		block.type = (FLAC__MetadataType)type;
		block.length = length;

		if(type == FLAC__METADATA_TYPE_APPLICATION) {
			if(!FLAC__bitreader_read_byte_block_aligned_no_crc(decoder->private_->input, block.data.application.id, FLAC__STREAM_METADATA_APPLICATION_ID_LEN/8))
				return false; /* read_callback_ sets the state for us */

			if(real_length < FLAC__STREAM_METADATA_APPLICATION_ID_LEN/8) { /* underflow check */
				decoder->protected_->state = FLAC__STREAM_DECODER_MEMORY_ALLOCATION_ERROR;/*@@@@@@ maybe wrong error? need to resync?*/
				return false;
			}

			real_length -= FLAC__STREAM_METADATA_APPLICATION_ID_LEN/8;

			if(decoder->private_->metadata_filter_ids_count > 0 && has_id_filtered_(decoder, block.data.application.id))
				skip_it = !skip_it;
		}

		if(skip_it) {
			if(!FLAC__bitreader_skip_byte_block_aligned_no_crc(decoder->private_->input, real_length))
				return false; /* read_callback_ sets the state for us */
		}
		else {
			FLAC__bool ok = true;
			switch(type) {
				case FLAC__METADATA_TYPE_PADDING:
					/* skip the padding bytes */
					if(!FLAC__bitreader_skip_byte_block_aligned_no_crc(decoder->private_->input, real_length))
						ok = false; /* read_callback_ sets the state for us */
					break;
				case FLAC__METADATA_TYPE_APPLICATION:
					/* remember, we read the ID already */
					if(real_length > 0) {
						if(0 == (block.data.application.data = (FLAC__byte*)malloc(real_length))) {
							decoder->protected_->state = FLAC__STREAM_DECODER_MEMORY_ALLOCATION_ERROR;
							ok = false;
						}
						else if(!FLAC__bitreader_read_byte_block_aligned_no_crc(decoder->private_->input, block.data.application.data, real_length))
							ok = false; /* read_callback_ sets the state for us */
					}
					else
						block.data.application.data = 0;
					break;
				case FLAC__METADATA_TYPE_VORBIS_COMMENT:
					if(!read_metadata_vorbiscomment_(decoder, &block.data.vorbis_comment, real_length))
						ok = false;
					break;
				case FLAC__METADATA_TYPE_CUESHEET:
					if(!read_metadata_cuesheet_(decoder, &block.data.cue_sheet))
						ok = false;
					break;
				case FLAC__METADATA_TYPE_PICTURE:
					if(!read_metadata_picture_(decoder, &block.data.picture))
						ok = false;
					break;
				case FLAC__METADATA_TYPE_STREAMINFO:
				case FLAC__METADATA_TYPE_SEEKTABLE:
					FLAC__ASSERT(0);
					break;
				default:
					if(real_length > 0) {
						if(0 == (block.data.unknown.data = (FLAC__byte*)malloc(real_length))) {
							decoder->protected_->state = FLAC__STREAM_DECODER_MEMORY_ALLOCATION_ERROR;
							ok = false;
						}
						else if(!FLAC__bitreader_read_byte_block_aligned_no_crc(decoder->private_->input, block.data.unknown.data, real_length))
							ok = false; /* read_callback_ sets the state for us */
					}
					else
						block.data.unknown.data = 0;
					break;
			}
			if(ok && !decoder->private_->is_seeking && decoder->private_->metadata_callback)
				decoder->private_->metadata_callback(decoder, &block, decoder->private_->client_data);

			/* now we have to free any malloc()ed data in the block */
			switch(type) {
				case FLAC__METADATA_TYPE_PADDING:
					break;
				case FLAC__METADATA_TYPE_APPLICATION:
					if(0 != block.data.application.data)
						free(block.data.application.data);
					break;
				case FLAC__METADATA_TYPE_VORBIS_COMMENT:
					if(0 != block.data.vorbis_comment.vendor_string.entry)
						free(block.data.vorbis_comment.vendor_string.entry);
					if(block.data.vorbis_comment.num_comments > 0)
						for(i = 0; i < block.data.vorbis_comment.num_comments; i++)
							if(0 != block.data.vorbis_comment.comments[i].entry)
								free(block.data.vorbis_comment.comments[i].entry);
					if(0 != block.data.vorbis_comment.comments)
						free(block.data.vorbis_comment.comments);
					break;
				case FLAC__METADATA_TYPE_CUESHEET:
					if(block.data.cue_sheet.num_tracks > 0)
						for(i = 0; i < block.data.cue_sheet.num_tracks; i++)
							if(0 != block.data.cue_sheet.tracks[i].indices)
								free(block.data.cue_sheet.tracks[i].indices);
					if(0 != block.data.cue_sheet.tracks)
						free(block.data.cue_sheet.tracks);
					break;
				case FLAC__METADATA_TYPE_PICTURE:
					if(0 != block.data.picture.mime_type)
						free(block.data.picture.mime_type);
					if(0 != block.data.picture.description)
						free(block.data.picture.description);
					if(0 != block.data.picture.data)
						free(block.data.picture.data);
					break;
				case FLAC__METADATA_TYPE_STREAMINFO:
				case FLAC__METADATA_TYPE_SEEKTABLE:
					FLAC__ASSERT(0);
				default:
					if(0 != block.data.unknown.data)
						free(block.data.unknown.data);
					break;
			}

			if(!ok) /* anything that unsets "ok" should also make sure decoder->protected_->state is updated */
				return false;
		}
	}

	if(is_last) {
		/* if this fails, it's OK, it's just a hint for the seek routine */
		if(!FLAC__stream_decoder_get_decode_position(decoder, &decoder->private_->first_frame_offset))
			decoder->private_->first_frame_offset = 0;
		decoder->protected_->state = FLAC__STREAM_DECODER_SEARCH_FOR_FRAME_SYNC;
	}

	return true;
}