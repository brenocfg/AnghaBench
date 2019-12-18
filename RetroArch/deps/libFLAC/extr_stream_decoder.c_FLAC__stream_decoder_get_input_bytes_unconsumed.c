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
struct TYPE_4__ {int /*<<< orphan*/  input; } ;
typedef  TYPE_2__ FLAC__StreamDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC__ASSERT (int) ; 
 int FLAC__bitreader_get_input_bits_unconsumed (int /*<<< orphan*/ ) ; 
 int FLAC__bitreader_is_consumed_byte_aligned (int /*<<< orphan*/ ) ; 

unsigned FLAC__stream_decoder_get_input_bytes_unconsumed(const FLAC__StreamDecoder *decoder)
{
	FLAC__ASSERT(0 != decoder);
	FLAC__ASSERT(FLAC__bitreader_is_consumed_byte_aligned(decoder->private_->input));
	FLAC__ASSERT(!(FLAC__bitreader_get_input_bits_unconsumed(decoder->private_->input) & 7));
	return FLAC__bitreader_get_input_bits_unconsumed(decoder->private_->input) / 8;
}