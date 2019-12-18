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
typedef  int uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* add_paeth_prediction ) (int*,int*,int*,int,int) ;int /*<<< orphan*/  (* add_bytes_l2 ) (int*,int*,int*,int) ;} ;
typedef  TYPE_1__ PNGDSPContext ;

/* Variables and functions */
 int /*<<< orphan*/  OP_AVG ; 
 int /*<<< orphan*/  OP_SUB ; 
#define  PNG_FILTER_VALUE_AVG 132 
#define  PNG_FILTER_VALUE_NONE 131 
#define  PNG_FILTER_VALUE_PAETH 130 
#define  PNG_FILTER_VALUE_SUB 129 
#define  PNG_FILTER_VALUE_UP 128 
 int /*<<< orphan*/  UNROLL_FILTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_add_png_paeth_prediction (int*,int*,int*,int,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  stub1 (int*,int*,int*,int) ; 
 int /*<<< orphan*/  stub2 (int*,int*,int*,int,int) ; 

__attribute__((used)) static void png_filter_row(PNGDSPContext *dsp, uint8_t *dst, int filter_type,
                           uint8_t *src, uint8_t *last, int size, int bpp)
{
    int i, p, r, g, b, a;

    switch (filter_type) {
    case PNG_FILTER_VALUE_NONE:
        memcpy(dst, src, size);
        break;
    case PNG_FILTER_VALUE_SUB:
        for (i = 0; i < bpp; i++)
            dst[i] = src[i];
        if (bpp == 4) {
            p = *(int *)dst;
            for (; i < size; i += bpp) {
                unsigned s = *(int *)(src + i);
                p = ((s & 0x7f7f7f7f) + (p & 0x7f7f7f7f)) ^ ((s ^ p) & 0x80808080);
                *(int *)(dst + i) = p;
            }
        } else {
#define OP_SUB(x, s, l) ((x) + (s))
            UNROLL_FILTER(OP_SUB);
        }
        break;
    case PNG_FILTER_VALUE_UP:
        dsp->add_bytes_l2(dst, src, last, size);
        break;
    case PNG_FILTER_VALUE_AVG:
        for (i = 0; i < bpp; i++) {
            p      = (last[i] >> 1);
            dst[i] = p + src[i];
        }
#define OP_AVG(x, s, l) (((((x) + (l)) >> 1) + (s)) & 0xff)
        UNROLL_FILTER(OP_AVG);
        break;
    case PNG_FILTER_VALUE_PAETH:
        for (i = 0; i < bpp; i++) {
            p      = last[i];
            dst[i] = p + src[i];
        }
        if (bpp > 2 && size > 4) {
            /* would write off the end of the array if we let it process
             * the last pixel with bpp=3 */
            int w = (bpp & 3) ? size - 3 : size;

            if (w > i) {
                dsp->add_paeth_prediction(dst + i, src + i, last + i, size - i, bpp);
                i = w;
            }
        }
        ff_add_png_paeth_prediction(dst + i, src + i, last + i, size - i, bpp);
        break;
    }
}