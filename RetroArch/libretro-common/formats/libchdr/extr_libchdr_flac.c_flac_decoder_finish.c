#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {scalar_t__ compressed_length; scalar_t__ custom_header; int /*<<< orphan*/  const* compressed_start; int /*<<< orphan*/  decoder; } ;
typedef  TYPE_1__ flac_decoder ;
typedef  scalar_t__ FLAC__uint64 ;
typedef  int /*<<< orphan*/  FLAC__byte ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC__stream_decoder_finish (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLAC__stream_decoder_get_decode_position (int /*<<< orphan*/ ,scalar_t__*) ; 

uint32_t flac_decoder_finish(flac_decoder* decoder)
{
	/* get the final decoding position and move forward */
	FLAC__uint64 position = 0;
	FLAC__stream_decoder_get_decode_position(decoder->decoder, &position);
	FLAC__stream_decoder_finish(decoder->decoder);

	/* adjust position if we provided the header */
	if (position == 0)
		return 0;
	if (decoder->compressed_start == (const FLAC__byte *)(decoder->custom_header))
		position -= decoder->compressed_length;
	return (uint32_t)position;
}