#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int fill_mode; scalar_t__ num_coded_vals; int ch_num; void* split_point; } ;
struct TYPE_5__ {scalar_t__ num_quant_units; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ Atrac3pChanUnitCtx ;
typedef  TYPE_2__ Atrac3pChanParams ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int num_coded_units(GetBitContext *gb, Atrac3pChanParams *chan,
                           Atrac3pChanUnitCtx *ctx, AVCodecContext *avctx)
{
    chan->fill_mode = get_bits(gb, 2);
    if (!chan->fill_mode) {
        chan->num_coded_vals = ctx->num_quant_units;
    } else {
        chan->num_coded_vals = get_bits(gb, 5);
        if (chan->num_coded_vals > ctx->num_quant_units) {
            av_log(avctx, AV_LOG_ERROR,
                   "Invalid number of transmitted units!\n");
            return AVERROR_INVALIDDATA;
        }

        if (chan->fill_mode == 3)
            chan->split_point = get_bits(gb, 2) + (chan->ch_num << 1) + 1;
    }

    return 0;
}