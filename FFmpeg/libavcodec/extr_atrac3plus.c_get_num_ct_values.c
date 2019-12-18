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
struct TYPE_3__ {int used_quant_units; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ Atrac3pChanUnitCtx ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_num_ct_values(GetBitContext *gb, Atrac3pChanUnitCtx *ctx,
                             AVCodecContext *avctx)
{
    int num_coded_vals;

    if (get_bits1(gb)) {
        num_coded_vals = get_bits(gb, 5);
        if (num_coded_vals > ctx->used_quant_units) {
            av_log(avctx, AV_LOG_ERROR,
                   "Invalid number of code table indexes: %d!\n", num_coded_vals);
            return AVERROR_INVALIDDATA;
        }
        return num_coded_vals;
    } else
        return ctx->used_quant_units;
}