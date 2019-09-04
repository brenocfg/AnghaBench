#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  enum TwinVQFrameType { ____Placeholder_TwinVQFrameType } TwinVQFrameType ;
struct TYPE_9__ {int size; } ;
typedef  TYPE_3__ TwinVQModeTab ;
struct TYPE_10__ {float* prev_frame; int* last_block_pos; float* curr_frame; TYPE_2__* fdsp; TYPE_1__* avctx; scalar_t__ spectrum; TYPE_3__* mtab; } ;
typedef  TYPE_4__ TwinVQContext ;
struct TYPE_8__ {int /*<<< orphan*/  (* butterflies_float ) (float*,float*,int) ;} ;
struct TYPE_7__ {int channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  imdct_and_window (TYPE_4__*,int,int,scalar_t__,float*,int) ; 
 int /*<<< orphan*/  memcpy (float*,float*,int) ; 
 int /*<<< orphan*/  stub1 (float*,float*,int) ; 

__attribute__((used)) static void imdct_output(TwinVQContext *tctx, enum TwinVQFrameType ftype,
                         int wtype, float **out, int offset)
{
    const TwinVQModeTab *mtab = tctx->mtab;
    float *prev_buf           = tctx->prev_frame + tctx->last_block_pos[0];
    int size1, size2, i;
    float *out1, *out2;

    for (i = 0; i < tctx->avctx->channels; i++)
        imdct_and_window(tctx, ftype, wtype,
                         tctx->spectrum + i * mtab->size,
                         prev_buf + 2 * i * mtab->size,
                         i);

    if (!out)
        return;

    size2 = tctx->last_block_pos[0];
    size1 = mtab->size - size2;

    out1 = &out[0][0] + offset;
    memcpy(out1,         prev_buf,         size1 * sizeof(*out1));
    memcpy(out1 + size1, tctx->curr_frame, size2 * sizeof(*out1));

    if (tctx->avctx->channels == 2) {
        out2 = &out[1][0] + offset;
        memcpy(out2, &prev_buf[2 * mtab->size],
               size1 * sizeof(*out2));
        memcpy(out2 + size1, &tctx->curr_frame[2 * mtab->size],
               size2 * sizeof(*out2));
        tctx->fdsp->butterflies_float(out1, out2, mtab->size);
    }
}