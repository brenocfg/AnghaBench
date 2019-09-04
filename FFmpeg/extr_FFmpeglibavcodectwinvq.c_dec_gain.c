#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  enum TwinVQFrameType { ____Placeholder_TwinVQFrameType } TwinVQFrameType ;
struct TYPE_9__ {TYPE_1__* fmode; } ;
typedef  TYPE_3__ TwinVQModeTab ;
struct TYPE_10__ {float* gain_bits; float* sub_gain_bits; } ;
typedef  TYPE_4__ TwinVQFrameData ;
struct TYPE_11__ {size_t cur_frame; TYPE_2__* avctx; TYPE_4__* bits; TYPE_3__* mtab; } ;
typedef  TYPE_5__ TwinVQContext ;
struct TYPE_8__ {int channels; } ;
struct TYPE_7__ {int sub; } ;

/* Variables and functions */
 int TWINVQ_AMP_MAX ; 
 int TWINVQ_FT_LONG ; 
 int TWINVQ_GAIN_BITS ; 
 int /*<<< orphan*/  TWINVQ_MULAW_MU ; 
 int TWINVQ_SUB_AMP_MAX ; 
 int TWINVQ_SUB_GAIN_BITS ; 
 float twinvq_mulawinv (float,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dec_gain(TwinVQContext *tctx,
                     enum TwinVQFrameType ftype, float *out)
{
    const TwinVQModeTab   *mtab =  tctx->mtab;
    const TwinVQFrameData *bits = &tctx->bits[tctx->cur_frame];
    int i, j;
    int sub        = mtab->fmode[ftype].sub;
    float step     = TWINVQ_AMP_MAX     / ((1 << TWINVQ_GAIN_BITS)     - 1);
    float sub_step = TWINVQ_SUB_AMP_MAX / ((1 << TWINVQ_SUB_GAIN_BITS) - 1);

    if (ftype == TWINVQ_FT_LONG) {
        for (i = 0; i < tctx->avctx->channels; i++)
            out[i] = (1.0 / (1 << 13)) *
                     twinvq_mulawinv(step * 0.5 + step * bits->gain_bits[i],
                                     TWINVQ_AMP_MAX, TWINVQ_MULAW_MU);
    } else {
        for (i = 0; i < tctx->avctx->channels; i++) {
            float val = (1.0 / (1 << 23)) *
                        twinvq_mulawinv(step * 0.5 + step * bits->gain_bits[i],
                                        TWINVQ_AMP_MAX, TWINVQ_MULAW_MU);

            for (j = 0; j < sub; j++)
                out[i * sub + j] =
                    val * twinvq_mulawinv(sub_step * 0.5 +
                                          sub_step * bits->sub_gain_bits[i * sub + j],
                                          TWINVQ_SUB_AMP_MAX, TWINVQ_MULAW_MU);
        }
    }
}