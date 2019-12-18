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
struct TYPE_15__ {TYPE_5__* private_; TYPE_4__* protected_; } ;
struct TYPE_10__ {scalar_t__ points; } ;
struct TYPE_11__ {TYPE_1__ seek_table; } ;
struct TYPE_12__ {TYPE_2__ data; } ;
struct TYPE_14__ {int internal_reset_hack; scalar_t__ file; scalar_t__ (* seek_callback ) (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int has_stream_info; int has_seek_table; scalar_t__ unparseable_frame_count; scalar_t__ first_frame_offset; int /*<<< orphan*/  md5context; scalar_t__ next_fixed_block_size; scalar_t__ fixed_block_size; int /*<<< orphan*/  do_md5_checking; TYPE_3__ seek_table; int /*<<< orphan*/  client_data; scalar_t__ is_ogg; } ;
struct TYPE_13__ {int /*<<< orphan*/  md5_checking; int /*<<< orphan*/  state; int /*<<< orphan*/  ogg_decoder_aspect; } ;
typedef  int FLAC__bool ;
typedef  TYPE_6__ FLAC__StreamDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC__ASSERT (int) ; 
 int /*<<< orphan*/  FLAC__MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FLAC__STREAM_DECODER_SEARCH_FOR_METADATA ; 
 scalar_t__ FLAC__STREAM_DECODER_SEEK_STATUS_ERROR ; 
 int /*<<< orphan*/  FLAC__ogg_decoder_aspect_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FLAC__stream_decoder_flush (TYPE_6__*) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ stdin ; 
 scalar_t__ stub1 (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

FLAC__bool FLAC__stream_decoder_reset(FLAC__StreamDecoder *decoder)
{
	FLAC__ASSERT(0 != decoder);
	FLAC__ASSERT(0 != decoder->private_);
	FLAC__ASSERT(0 != decoder->protected_);

	if(!FLAC__stream_decoder_flush(decoder)) {
		/* above call sets the state for us */
		return false;
	}

#if FLAC__HAS_OGG
	/*@@@ could go in !internal_reset_hack block below */
	if(decoder->private_->is_ogg)
		FLAC__ogg_decoder_aspect_reset(&decoder->protected_->ogg_decoder_aspect);
#endif

	/* Rewind if necessary.  If FLAC__stream_decoder_init() is calling us,
	 * (internal_reset_hack) don't try to rewind since we are already at
	 * the beginning of the stream and don't want to fail if the input is
	 * not seekable.
	 */
	if(!decoder->private_->internal_reset_hack) {
		if(decoder->private_->file == stdin)
			return false; /* can't rewind stdin, reset fails */
		if(decoder->private_->seek_callback && decoder->private_->seek_callback(decoder, 0, decoder->private_->client_data) == FLAC__STREAM_DECODER_SEEK_STATUS_ERROR)
			return false; /* seekable and seek fails, reset fails */
	}
	else
		decoder->private_->internal_reset_hack = false;

	decoder->protected_->state = FLAC__STREAM_DECODER_SEARCH_FOR_METADATA;

	decoder->private_->has_stream_info = false;

	free(decoder->private_->seek_table.data.seek_table.points);
	decoder->private_->seek_table.data.seek_table.points = 0;
	decoder->private_->has_seek_table = false;

	decoder->private_->do_md5_checking = decoder->protected_->md5_checking;
	/*
	 * This goes in reset() and not flush() because according to the spec, a
	 * fixed-blocksize stream must stay that way through the whole stream.
	 */
	decoder->private_->fixed_block_size = decoder->private_->next_fixed_block_size = 0;

	/* We initialize the FLAC__MD5Context even though we may never use it.  This
	 * is because md5 checking may be turned on to start and then turned off if
	 * a seek occurs.  So we init the context here and finalize it in
	 * FLAC__stream_decoder_finish() to make sure things are always cleaned up
	 * properly.
	 */
	FLAC__MD5Init(&decoder->private_->md5context);

	decoder->private_->first_frame_offset = 0;
	decoder->private_->unparseable_frame_count = 0;

	return true;
}