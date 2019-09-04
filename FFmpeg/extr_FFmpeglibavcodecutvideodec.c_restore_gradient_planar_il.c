#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int ptrdiff_t ;
struct TYPE_4__ {int (* add_left_pred ) (int*,int*,int,int) ;int /*<<< orphan*/  (* add_gradient_pred ) (int*,int const,int) ;} ;
struct TYPE_5__ {TYPE_1__ llviddsp; } ;
typedef  TYPE_2__ UtvideoContext ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int stub1 (int*,int*,int,int) ; 
 int stub2 (int*,int*,int,int) ; 
 int /*<<< orphan*/  stub3 (int*,int const,int) ; 

__attribute__((used)) static void restore_gradient_planar_il(UtvideoContext *c, uint8_t *src, ptrdiff_t stride,
                                      int width, int height, int slices, int rmode)
{
    int i, j, slice;
    int A, B, C;
    uint8_t *bsrc;
    int slice_start, slice_height;
    const int cmask   = ~(rmode ? 3 : 1);
    const ptrdiff_t stride2 = stride << 1;
    int min_width = FFMIN(width, 32);

    for (slice = 0; slice < slices; slice++) {
        slice_start    = ((slice * height) / slices) & cmask;
        slice_height   = ((((slice + 1) * height) / slices) & cmask) -
                         slice_start;
        slice_height >>= 1;
        if (!slice_height)
            continue;

        bsrc = src + slice_start * stride;

        // first line - left neighbour prediction
        bsrc[0] += 0x80;
        A = c->llviddsp.add_left_pred(bsrc, bsrc, width, 0);
        c->llviddsp.add_left_pred(bsrc + stride, bsrc + stride, width, A);
        bsrc += stride2;
        if (slice_height <= 1)
            continue;
        for (j = 1; j < slice_height; j++) {
            // second line - first element has top prediction, the rest uses gradient
            bsrc[0] = (bsrc[0] + bsrc[-stride2]) & 0xFF;
            for (i = 1; i < min_width; i++) { /* dsp need align 32 */
                A = bsrc[i - stride2];
                B = bsrc[i - (stride2 + 1)];
                C = bsrc[i - 1];
                bsrc[i] = (A - B + C + bsrc[i]) & 0xFF;
            }
            if (width > 32)
                c->llviddsp.add_gradient_pred(bsrc + 32, stride2, width - 32);

            A = bsrc[-stride];
            B = bsrc[-(1 + stride + stride - width)];
            C = bsrc[width - 1];
            bsrc[stride] = (A - B + C + bsrc[stride]) & 0xFF;
            for (i = 1; i < width; i++) {
                A = bsrc[i - stride];
                B = bsrc[i - (1 + stride)];
                C = bsrc[i - 1 + stride];
                bsrc[i + stride] = (A - B + C + bsrc[i + stride]) & 0xFF;
            }
            bsrc += stride2;
        }
    }
}