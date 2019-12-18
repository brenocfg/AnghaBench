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
typedef  int FLAC__uint32 ;
typedef  int FLAC__bool ;
typedef  TYPE_2__ FLAC__StreamDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC__bitreader_read_raw_uint32 (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  FLAC__bitreader_skip_byte_block_aligned_no_crc (int /*<<< orphan*/ ,unsigned int) ; 

FLAC__bool skip_id3v2_tag_(FLAC__StreamDecoder *decoder)
{
	FLAC__uint32 x;
	unsigned i, skip;

	/* skip the version and flags bytes */
	if(!FLAC__bitreader_read_raw_uint32(decoder->private_->input, &x, 24))
		return false; /* read_callback_ sets the state for us */
	/* get the size (in bytes) to skip */
	skip = 0;
	for(i = 0; i < 4; i++) {
		if(!FLAC__bitreader_read_raw_uint32(decoder->private_->input, &x, 8))
			return false; /* read_callback_ sets the state for us */
		skip <<= 7;
		skip |= (x & 0x7f);
	}
	/* skip the rest of the tag */
	if(!FLAC__bitreader_skip_byte_block_aligned_no_crc(decoder->private_->input, skip))
		return false; /* read_callback_ sets the state for us */
	return true;
}