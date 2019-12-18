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
struct TYPE_5__ {TYPE_1__* private_; } ;
struct TYPE_4__ {int /*<<< orphan*/  file; } ;
typedef  int /*<<< orphan*/  FLAC__byte ;
typedef  int /*<<< orphan*/  FLAC__StreamDecoderReadStatus ;
typedef  TYPE_2__ FLAC__StreamDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC__STREAM_DECODER_READ_STATUS_ABORT ; 
 int /*<<< orphan*/  FLAC__STREAM_DECODER_READ_STATUS_CONTINUE ; 
 int /*<<< orphan*/  FLAC__STREAM_DECODER_READ_STATUS_END_OF_STREAM ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 size_t fread (int /*<<< orphan*/ *,int,size_t,int /*<<< orphan*/ ) ; 

FLAC__StreamDecoderReadStatus file_read_callback_(const FLAC__StreamDecoder *decoder, FLAC__byte buffer[], size_t *bytes, void *client_data)
{
	(void)client_data;

	if(*bytes > 0) {
		*bytes = fread(buffer, sizeof(FLAC__byte), *bytes, decoder->private_->file);
		if(ferror(decoder->private_->file))
			return FLAC__STREAM_DECODER_READ_STATUS_ABORT;
		else if(*bytes == 0)
			return FLAC__STREAM_DECODER_READ_STATUS_END_OF_STREAM;
		else
			return FLAC__STREAM_DECODER_READ_STATUS_CONTINUE;
	}
	else
		return FLAC__STREAM_DECODER_READ_STATUS_ABORT; /* abort to avoid a deadlock */
}