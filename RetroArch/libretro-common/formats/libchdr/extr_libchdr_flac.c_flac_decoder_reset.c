#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  s_header_template ;
struct TYPE_4__ {int* custom_header; int compressed_length; int compressed2_length; int /*<<< orphan*/  const* compressed2_start; int /*<<< orphan*/  const* compressed_start; } ;
typedef  TYPE_1__ flac_decoder ;
typedef  int /*<<< orphan*/  FLAC__byte ;

/* Variables and functions */
 int flac_decoder_internal_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 

int flac_decoder_reset(flac_decoder* decoder, uint32_t sample_rate, uint8_t num_channels, uint32_t block_size, const void *buffer, uint32_t length)
{
	/* modify the template header with our parameters */
	static const uint8_t s_header_template[0x2a] =
	{
		0x66, 0x4C, 0x61, 0x43,                         /* +00: 'fLaC' stream header */
		0x80,                                           /* +04: metadata block type 0 (STREAMINFO), */
								/*      flagged as last block */
		0x00, 0x00, 0x22,                               /* +05: metadata block length = 0x22 */
		0x00, 0x00,                                     /* +08: minimum block size */
		0x00, 0x00,                                     /* +0A: maximum block size */
		0x00, 0x00, 0x00,                               /* +0C: minimum frame size (0 == unknown) */
		0x00, 0x00, 0x00,                               /* +0F: maximum frame size (0 == unknown) */
		0x0A, 0xC4, 0x42, 0xF0, 0x00, 0x00, 0x00, 0x00, /* +12: sample rate (0x0ac44 == 44100), */
								/*      numchannels (2), sample bits (16), */
								/*      samples in stream (0 == unknown) */
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* +1A: MD5 signature (0 == none) */
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  /* +2A: start of stream data */
	};
	memcpy(decoder->custom_header, s_header_template, sizeof(s_header_template));
	decoder->custom_header[0x08] = decoder->custom_header[0x0a] = block_size >> 8;
	decoder->custom_header[0x09] = decoder->custom_header[0x0b] = block_size & 0xff;
	decoder->custom_header[0x12] = sample_rate >> 12;
	decoder->custom_header[0x13] = sample_rate >> 4;
	decoder->custom_header[0x14] = (sample_rate << 4) | ((num_channels - 1) << 1);

	/* configure the header ahead of the provided buffer */
	decoder->compressed_start = (const FLAC__byte *)(decoder->custom_header);
	decoder->compressed_length = sizeof(decoder->custom_header);
	decoder->compressed2_start = (const FLAC__byte *)(buffer);
	decoder->compressed2_length = length;
	return flac_decoder_internal_reset(decoder);
}