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
struct TYPE_7__ {TYPE_2__* protected_; TYPE_1__* private_; } ;
struct TYPE_6__ {scalar_t__ state; int /*<<< orphan*/  ogg_decoder_aspect; } ;
struct TYPE_5__ {int do_md5_checking; int /*<<< orphan*/  input; scalar_t__ is_ogg; scalar_t__ samples_decoded; int /*<<< orphan*/  internal_reset_hack; } ;
typedef  int FLAC__bool ;
typedef  TYPE_3__ FLAC__StreamDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC__ASSERT (int) ; 
 scalar_t__ FLAC__STREAM_DECODER_MEMORY_ALLOCATION_ERROR ; 
 scalar_t__ FLAC__STREAM_DECODER_SEARCH_FOR_FRAME_SYNC ; 
 scalar_t__ FLAC__STREAM_DECODER_UNINITIALIZED ; 
 int /*<<< orphan*/  FLAC__bitreader_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLAC__ogg_decoder_aspect_flush (int /*<<< orphan*/ *) ; 

FLAC__bool FLAC__stream_decoder_flush(FLAC__StreamDecoder *decoder)
{
	FLAC__ASSERT(0 != decoder);
	FLAC__ASSERT(0 != decoder->private_);
	FLAC__ASSERT(0 != decoder->protected_);

	if(!decoder->private_->internal_reset_hack && decoder->protected_->state == FLAC__STREAM_DECODER_UNINITIALIZED)
		return false;

	decoder->private_->samples_decoded = 0;
	decoder->private_->do_md5_checking = false;

#if FLAC__HAS_OGG
	if(decoder->private_->is_ogg)
		FLAC__ogg_decoder_aspect_flush(&decoder->protected_->ogg_decoder_aspect);
#endif

	if(!FLAC__bitreader_clear(decoder->private_->input)) {
		decoder->protected_->state = FLAC__STREAM_DECODER_MEMORY_ALLOCATION_ERROR;
		return false;
	}
	decoder->protected_->state = FLAC__STREAM_DECODER_SEARCH_FOR_FRAME_SYNC;

	return true;
}