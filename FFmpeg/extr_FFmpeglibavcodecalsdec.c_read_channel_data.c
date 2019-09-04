#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int channels; } ;
struct TYPE_7__ {unsigned int master_channel; scalar_t__ time_diff_index; void* time_diff_sign; void** weighting; void* time_diff_flag; void* stop_flag; } ;
struct TYPE_6__ {TYPE_5__* avctx; scalar_t__ ltp_lag_length; int /*<<< orphan*/  gb; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ ALSDecContext ;
typedef  TYPE_2__ ALSChannelData ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  align_get_bits (int /*<<< orphan*/ *) ; 
 void* als_weighting (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  av_ceil_log2 (unsigned int) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ get_bits (int /*<<< orphan*/ *,scalar_t__) ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 
 unsigned int get_bits_long (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_channel_data(ALSDecContext *ctx, ALSChannelData *cd, int c)
{
    GetBitContext *gb       = &ctx->gb;
    ALSChannelData *current = cd;
    unsigned int channels   = ctx->avctx->channels;
    int entries             = 0;

    while (entries < channels && !(current->stop_flag = get_bits1(gb))) {
        current->master_channel = get_bits_long(gb, av_ceil_log2(channels));

        if (current->master_channel >= channels) {
            av_log(ctx->avctx, AV_LOG_ERROR, "Invalid master channel.\n");
            return AVERROR_INVALIDDATA;
        }

        if (current->master_channel != c) {
            current->time_diff_flag = get_bits1(gb);
            current->weighting[0]   = als_weighting(gb, 1, 16);
            current->weighting[1]   = als_weighting(gb, 2, 14);
            current->weighting[2]   = als_weighting(gb, 1, 16);

            if (current->time_diff_flag) {
                current->weighting[3] = als_weighting(gb, 1, 16);
                current->weighting[4] = als_weighting(gb, 1, 16);
                current->weighting[5] = als_weighting(gb, 1, 16);

                current->time_diff_sign  = get_bits1(gb);
                current->time_diff_index = get_bits(gb, ctx->ltp_lag_length - 3) + 3;
            }
        }

        current++;
        entries++;
    }

    if (entries == channels) {
        av_log(ctx->avctx, AV_LOG_ERROR, "Damaged channel data.\n");
        return AVERROR_INVALIDDATA;
    }

    align_get_bits(gb);
    return 0;
}