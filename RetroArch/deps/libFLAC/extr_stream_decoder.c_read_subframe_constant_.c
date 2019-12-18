#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_5__* private_; } ;
struct TYPE_14__ {int /*<<< orphan*/  value; } ;
struct TYPE_11__ {unsigned int blocksize; } ;
struct TYPE_12__ {TYPE_3__ header; TYPE_2__* subframes; } ;
struct TYPE_13__ {TYPE_4__ frame; int /*<<< orphan*/  input; int /*<<< orphan*/ ** output; } ;
struct TYPE_9__ {TYPE_6__ constant; } ;
struct TYPE_10__ {int /*<<< orphan*/  type; TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  FLAC__int32 ;
typedef  int FLAC__bool ;
typedef  TYPE_6__ FLAC__Subframe_Constant ;
typedef  TYPE_7__ FLAC__StreamDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC__SUBFRAME_TYPE_CONSTANT ; 
 int /*<<< orphan*/  FLAC__bitreader_read_raw_int32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 

FLAC__bool read_subframe_constant_(FLAC__StreamDecoder *decoder, unsigned channel, unsigned bps, FLAC__bool do_full_decode)
{
	FLAC__Subframe_Constant *subframe = &decoder->private_->frame.subframes[channel].data.constant;
	FLAC__int32 x;
	unsigned i;
	FLAC__int32 *output = decoder->private_->output[channel];

	decoder->private_->frame.subframes[channel].type = FLAC__SUBFRAME_TYPE_CONSTANT;

	if(!FLAC__bitreader_read_raw_int32(decoder->private_->input, &x, bps))
		return false; /* read_callback_ sets the state for us */

	subframe->value = x;

	/* decode the subframe */
	if(do_full_decode) {
		for(i = 0; i < decoder->private_->frame.header.blocksize; i++)
			output[i] = x;
	}

	return true;
}