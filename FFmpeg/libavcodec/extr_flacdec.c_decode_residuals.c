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
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {int blocksize; int /*<<< orphan*/  gb; int /*<<< orphan*/  avctx; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ FLACContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int INT_MAX ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_sbits_long (int /*<<< orphan*/ *,int) ; 
 int get_sr_golomb_flac (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_residuals(FLACContext *s, int32_t *decoded, int pred_order)
{
    GetBitContext gb = s->gb;
    int i, tmp, partition, method_type, rice_order;
    int rice_bits, rice_esc;
    int samples;

    method_type = get_bits(&gb, 2);
    rice_order  = get_bits(&gb, 4);

    samples   = s->blocksize >> rice_order;
    rice_bits = 4 + method_type;
    rice_esc  = (1 << rice_bits) - 1;

    decoded += pred_order;
    i        = pred_order;

    if (method_type > 1) {
        av_log(s->avctx, AV_LOG_ERROR, "illegal residual coding method %d\n",
               method_type);
        return AVERROR_INVALIDDATA;
    }

    if (samples << rice_order != s->blocksize) {
        av_log(s->avctx, AV_LOG_ERROR, "invalid rice order: %i blocksize %i\n",
               rice_order, s->blocksize);
        return AVERROR_INVALIDDATA;
    }

    if (pred_order > samples) {
        av_log(s->avctx, AV_LOG_ERROR, "invalid predictor order: %i > %i\n",
               pred_order, samples);
        return AVERROR_INVALIDDATA;
    }

    for (partition = 0; partition < (1 << rice_order); partition++) {
        tmp = get_bits(&gb, rice_bits);
        if (tmp == rice_esc) {
            tmp = get_bits(&gb, 5);
            for (; i < samples; i++)
                *decoded++ = get_sbits_long(&gb, tmp);
        } else {
            int real_limit = tmp ? (INT_MAX >> tmp) + 2 : INT_MAX;
            for (; i < samples; i++) {
                int v = get_sr_golomb_flac(&gb, tmp, real_limit, 0);
                if (v == 0x80000000){
                    av_log(s->avctx, AV_LOG_ERROR, "invalid residual\n");
                    return AVERROR_INVALIDDATA;
                }

                *decoded++ = v;
            }
        }
        i= 0;
    }

    s->gb = gb;

    return 0;
}