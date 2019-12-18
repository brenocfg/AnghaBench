#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int int16_t ;
struct TYPE_5__ {int err_recognition; } ;
struct TYPE_4__ {int y_dc_scale; int c_dc_scale; int* block_wrap; int** dc_val; int* block_index; scalar_t__ mb_x; scalar_t__ resync_mb_x; scalar_t__ mb_y; scalar_t__ resync_mb_y; int workaround_bugs; TYPE_3__* avctx; int /*<<< orphan*/  encoding; scalar_t__ first_slice_line; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AV_EF_AGGRESSIVE ; 
 int AV_EF_BITSTREAM ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int FASTDIV (int,int) ; 
 int FF_BUG_DC_CLIP ; 
 scalar_t__ IS_3IV1 ; 
 scalar_t__ abs (int) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline int ff_mpeg4_pred_dc(MpegEncContext *s, int n, int level,
                                   int *dir_ptr, int encoding)
{
    int a, b, c, wrap, pred, scale, ret;
    int16_t *dc_val;

    /* find prediction */
    if (n < 4)
        scale = s->y_dc_scale;
    else
        scale = s->c_dc_scale;
    if (IS_3IV1)
        scale = 8;

    wrap   = s->block_wrap[n];
    dc_val = s->dc_val[0] + s->block_index[n];

    /* B C
     * A X
     */
    a = dc_val[-1];
    b = dc_val[-1 - wrap];
    c = dc_val[-wrap];

    /* outside slice handling (we can't do that by memset as we need the
     * dc for error resilience) */
    if (s->first_slice_line && n != 3) {
        if (n != 2)
            b = c = 1024;
        if (n != 1 && s->mb_x == s->resync_mb_x)
            b = a = 1024;
    }
    if (s->mb_x == s->resync_mb_x && s->mb_y == s->resync_mb_y + 1) {
        if (n == 0 || n == 4 || n == 5)
            b = 1024;
    }

    if (abs(a - b) < abs(b - c)) {
        pred     = c;
        *dir_ptr = 1; /* top */
    } else {
        pred     = a;
        *dir_ptr = 0; /* left */
    }
    /* we assume pred is positive */
    pred = FASTDIV((pred + (scale >> 1)), scale);

    if (encoding) {
        ret = level - pred;
    } else {
        level += pred;
        ret    = level;
    }
    level *= scale;
    if (level & (~2047)) {
        if (!s->encoding && (s->avctx->err_recognition & (AV_EF_BITSTREAM | AV_EF_AGGRESSIVE))) {
            if (level < 0) {
                av_log(s->avctx, AV_LOG_ERROR,
                       "dc<0 at %dx%d\n", s->mb_x, s->mb_y);
                return AVERROR_INVALIDDATA;
            }
            if (level > 2048 + scale) {
                av_log(s->avctx, AV_LOG_ERROR,
                       "dc overflow at %dx%d\n", s->mb_x, s->mb_y);
                return AVERROR_INVALIDDATA;
            }
        }
        if (level < 0)
            level = 0;
        else if (!(s->workaround_bugs & FF_BUG_DC_CLIP))
            level = 2047;
    }
    dc_val[0] = level;

    return ret;
}