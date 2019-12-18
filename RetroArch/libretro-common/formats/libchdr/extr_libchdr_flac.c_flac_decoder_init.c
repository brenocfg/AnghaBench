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
struct TYPE_3__ {scalar_t__ uncompressed_swap; scalar_t__ uncompressed_length; scalar_t__ uncompressed_offset; scalar_t__ compressed2_length; int /*<<< orphan*/ * compressed2_start; scalar_t__ compressed_length; int /*<<< orphan*/ * compressed_start; scalar_t__ compressed_offset; scalar_t__ bits_per_sample; scalar_t__ channels; scalar_t__ sample_rate; int /*<<< orphan*/  decoder; } ;
typedef  TYPE_1__ flac_decoder ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC__stream_decoder_new () ; 

void flac_decoder_init(flac_decoder *decoder)
{
	decoder->decoder = FLAC__stream_decoder_new();
	decoder->sample_rate = 0;
	decoder->channels = 0;
	decoder->bits_per_sample = 0;
	decoder->compressed_offset = 0;
	decoder->compressed_start = NULL;
	decoder->compressed_length = 0;
	decoder->compressed2_start = NULL;
	decoder->compressed2_length = 0;
	decoder->uncompressed_offset = 0;
	decoder->uncompressed_length = 0;
	decoder->uncompressed_swap = 0;
}