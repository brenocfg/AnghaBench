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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_3__ {scalar_t__ uncompressed_offset; scalar_t__ uncompressed_length; int uncompressed_swap; int /*<<< orphan*/  decoder; int /*<<< orphan*/ ** uncompressed_start; } ;
typedef  TYPE_1__ flac_decoder ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC__stream_decoder_process_single (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 

int flac_decoder_decode_interleaved(flac_decoder* decoder, int16_t *samples, uint32_t num_samples, int swap_endian)
{
	/* configure the uncompressed buffer */
	memset(decoder->uncompressed_start, 0, sizeof(decoder->uncompressed_start));
	decoder->uncompressed_start[0] = samples;
	decoder->uncompressed_offset = 0;
	decoder->uncompressed_length = num_samples;
	decoder->uncompressed_swap = swap_endian;

	/* loop until we get everything we want */
	while (decoder->uncompressed_offset < decoder->uncompressed_length)
		if (!FLAC__stream_decoder_process_single(decoder->decoder))
			return 0;
	return 1;
}