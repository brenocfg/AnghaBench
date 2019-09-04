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
struct TYPE_4__ {int ch_mask; int frame_size; int /*<<< orphan*/  avctx; int /*<<< orphan*/  gb; int /*<<< orphan*/  nchannels; } ;
typedef  TYPE_1__ DCACoreDecoder ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int DCA_SPEAKER_MASK_Cs ; 
 int /*<<< orphan*/  HEADER_XCH ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ff_dca_seek_bits (int /*<<< orphan*/ *,int) ; 
 int parse_frame_data (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_xch_frame(DCACoreDecoder *s)
{
    int ret;

    if (s->ch_mask & DCA_SPEAKER_MASK_Cs) {
        av_log(s->avctx, AV_LOG_ERROR, "XCH with Cs speaker already present\n");
        return AVERROR_INVALIDDATA;
    }

    if ((ret = parse_frame_data(s, HEADER_XCH, s->nchannels)) < 0)
        return ret;

    // Seek to the end of core frame, don't trust XCH frame size
    if (ff_dca_seek_bits(&s->gb, s->frame_size * 8)) {
        av_log(s->avctx, AV_LOG_ERROR, "Read past end of XCH frame\n");
        return AVERROR_INVALIDDATA;
    }

    return 0;
}