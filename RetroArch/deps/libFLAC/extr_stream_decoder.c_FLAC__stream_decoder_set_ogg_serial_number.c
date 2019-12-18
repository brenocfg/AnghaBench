#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ private_; TYPE_1__* protected_; } ;
struct TYPE_4__ {scalar_t__ state; int /*<<< orphan*/  ogg_decoder_aspect; } ;
typedef  int FLAC__bool ;
typedef  TYPE_2__ FLAC__StreamDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC__ASSERT (int) ; 
 scalar_t__ FLAC__STREAM_DECODER_UNINITIALIZED ; 
 int /*<<< orphan*/  FLAC__ogg_decoder_aspect_set_serial_number (int /*<<< orphan*/ *,long) ; 

FLAC__bool FLAC__stream_decoder_set_ogg_serial_number(FLAC__StreamDecoder *decoder, long value)
{
	FLAC__ASSERT(0 != decoder);
	FLAC__ASSERT(0 != decoder->private_);
	FLAC__ASSERT(0 != decoder->protected_);
	if(decoder->protected_->state != FLAC__STREAM_DECODER_UNINITIALIZED)
		return false;
#if FLAC__HAS_OGG
	/* can't check decoder->private_->is_ogg since that's not set until init time */
	FLAC__ogg_decoder_aspect_set_serial_number(&decoder->protected_->ogg_decoder_aspect, value);
	return true;
#else
	(void)value;
	return false;
#endif
}