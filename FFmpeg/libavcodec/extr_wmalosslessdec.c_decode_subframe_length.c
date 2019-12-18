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
struct TYPE_3__ {int samples_per_frame; int min_samples_per_subframe; int /*<<< orphan*/  avctx; int /*<<< orphan*/  gb; scalar_t__ max_num_subframes; } ;
typedef  TYPE_1__ WmallDecodeCtx ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int av_log2 (scalar_t__) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int decode_subframe_length(WmallDecodeCtx *s, int offset)
{
    int frame_len_ratio, subframe_len, len;

    /* no need to read from the bitstream when only one length is possible */
    if (offset == s->samples_per_frame - s->min_samples_per_subframe)
        return s->min_samples_per_subframe;

    len             = av_log2(s->max_num_subframes - 1) + 1;
    frame_len_ratio = get_bits(&s->gb, len);
    subframe_len    = s->min_samples_per_subframe * (frame_len_ratio + 1);

    /* sanity check the length */
    if (subframe_len < s->min_samples_per_subframe ||
        subframe_len > s->samples_per_frame) {
        av_log(s->avctx, AV_LOG_ERROR, "broken frame: subframe_len %i\n",
               subframe_len);
        return AVERROR_INVALIDDATA;
    }
    return subframe_len;
}