#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_5__ {int** decoded; int frameflags; int /*<<< orphan*/  (* predictor_decode_stereo ) (TYPE_1__*,int) ;scalar_t__ error; int /*<<< orphan*/  (* entropy_decode_stereo ) (TYPE_1__*,int) ;int /*<<< orphan*/  avctx; } ;
typedef  TYPE_1__ APEContext ;

/* Variables and functions */
 int APE_FRAMECODE_STEREO_SILENCE ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int) ; 

__attribute__((used)) static void ape_unpack_stereo(APEContext *ctx, int count)
{
    unsigned left, right;
    int32_t *decoded0 = ctx->decoded[0];
    int32_t *decoded1 = ctx->decoded[1];

    if ((ctx->frameflags & APE_FRAMECODE_STEREO_SILENCE) == APE_FRAMECODE_STEREO_SILENCE) {
        /* We are pure silence, so we're done. */
        av_log(ctx->avctx, AV_LOG_DEBUG, "pure silence stereo\n");
        return;
    }

    ctx->entropy_decode_stereo(ctx, count);
    if (ctx->error)
        return;

    /* Now apply the predictor decoding */
    ctx->predictor_decode_stereo(ctx, count);

    /* Decorrelate and scale to output depth */
    while (count--) {
        left = *decoded1 - (unsigned)(*decoded0 / 2);
        right = left + *decoded0;

        *(decoded0++) = left;
        *(decoded1++) = right;
    }
}