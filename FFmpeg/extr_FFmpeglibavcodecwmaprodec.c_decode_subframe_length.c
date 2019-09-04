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
struct TYPE_3__ {int samples_per_frame; int min_samples_per_subframe; int /*<<< orphan*/  avctx; scalar_t__ subframe_len_bits; int /*<<< orphan*/  gb; scalar_t__ max_subframe_len_bit; } ;
typedef  TYPE_1__ WMAProDecodeCtx ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int get_bits (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_subframe_length(WMAProDecodeCtx *s, int offset)
{
    int frame_len_shift = 0;
    int subframe_len;

    /** no need to read from the bitstream when only one length is possible */
    if (offset == s->samples_per_frame - s->min_samples_per_subframe)
        return s->min_samples_per_subframe;

    if (get_bits_left(&s->gb) < 1)
        return AVERROR_INVALIDDATA;

    /** 1 bit indicates if the subframe is of maximum length */
    if (s->max_subframe_len_bit) {
        if (get_bits1(&s->gb))
            frame_len_shift = 1 + get_bits(&s->gb, s->subframe_len_bits-1);
    } else
        frame_len_shift = get_bits(&s->gb, s->subframe_len_bits);

    subframe_len = s->samples_per_frame >> frame_len_shift;

    /** sanity check the length */
    if (subframe_len < s->min_samples_per_subframe ||
        subframe_len > s->samples_per_frame) {
        av_log(s->avctx, AV_LOG_ERROR, "broken frame: subframe_len %i\n",
               subframe_len);
        return AVERROR_INVALIDDATA;
    }
    return subframe_len;
}