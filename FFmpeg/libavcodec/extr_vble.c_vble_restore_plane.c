#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* add_median_pred ) (int*,int*,int*,int,int*,int*) ;} ;
struct TYPE_7__ {int* val; TYPE_1__ llviddsp; } ;
typedef  TYPE_2__ VBLEContext ;
struct TYPE_8__ {int** data; int* linesize; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int*,int*,int*,int,int*,int*) ; 

__attribute__((used)) static void vble_restore_plane(VBLEContext *ctx, AVFrame *pic,
                               GetBitContext *gb, int plane,
                               int offset, int width, int height)
{
    uint8_t *dst = pic->data[plane];
    uint8_t *val = ctx->val + offset;
    int stride = pic->linesize[plane];
    int i, j, left, left_top;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            /* get_bits can't take a length of 0 */
            if (val[j]) {
                int v = (1 << val[j]) + get_bits(gb, val[j]) - 1;
                val[j] = (v >> 1) ^ -(v & 1);
            }
        }
        if (i) {
            left = 0;
            left_top = dst[-stride];
            ctx->llviddsp.add_median_pred(dst, dst - stride, val,
                                          width, &left, &left_top);
        } else {
            dst[0] = val[0];
            for (j = 1; j < width; j++)
                dst[j] = val[j] + dst[j - 1];
        }
        dst += stride;
        val += width;
    }
}