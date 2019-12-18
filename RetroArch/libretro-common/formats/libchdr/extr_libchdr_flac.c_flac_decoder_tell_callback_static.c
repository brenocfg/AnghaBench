#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  compressed_offset; } ;
typedef  TYPE_1__ flac_decoder ;
typedef  int /*<<< orphan*/  FLAC__uint64 ;
typedef  int /*<<< orphan*/  FLAC__StreamDecoderTellStatus ;
typedef  int /*<<< orphan*/  FLAC__StreamDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC__STREAM_DECODER_TELL_STATUS_OK ; 

FLAC__StreamDecoderTellStatus flac_decoder_tell_callback_static(const FLAC__StreamDecoder *decoder, FLAC__uint64 *absolute_byte_offset, void *client_data)
{
	*absolute_byte_offset = ((flac_decoder *)client_data)->compressed_offset;
	return FLAC__STREAM_DECODER_TELL_STATUS_OK;
}