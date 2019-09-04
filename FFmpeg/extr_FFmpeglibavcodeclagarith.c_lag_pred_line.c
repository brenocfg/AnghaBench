#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_6__ {int (* add_left_pred ) (int*,int*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {TYPE_1__* avctx; TYPE_2__ llviddsp; } ;
struct TYPE_5__ {scalar_t__ pix_fmt; } ;
typedef  TYPE_3__ LagarithContext ;

/* Variables and functions */
 scalar_t__ AV_PIX_FMT_YUV420P ; 
 int /*<<< orphan*/  add_lag_median_prediction (int*,int*,int*,int,int*,int*) ; 
 int stub1 (int*,int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lag_pred_line(LagarithContext *l, uint8_t *buf,
                          int width, int stride, int line)
{
    int L, TL;

    if (!line) {
        /* Left prediction only for first line */
        L = l->llviddsp.add_left_pred(buf, buf, width, 0);
    } else {
        /* Left pixel is actually prev_row[width] */
        L = buf[width - stride - 1];

        if (line == 1) {
            /* Second line, left predict first pixel, the rest of the line is median predicted
             * NOTE: In the case of RGB this pixel is top predicted */
            TL = l->avctx->pix_fmt == AV_PIX_FMT_YUV420P ? buf[-stride] : L;
        } else {
            /* Top left is 2 rows back, last pixel */
            TL = buf[width - (2 * stride) - 1];
        }

        add_lag_median_prediction(buf, buf - stride, buf,
                                  width, &L, &TL);
    }
}