#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* diff_bytes ) (int*,int*,int*,int) ;} ;
struct TYPE_6__ {TYPE_1__ llvidencdsp; } ;
typedef  TYPE_2__ PNGEncContext ;

/* Variables and functions */
#define  PNG_FILTER_VALUE_AVG 132 
#define  PNG_FILTER_VALUE_NONE 131 
#define  PNG_FILTER_VALUE_PAETH 130 
#define  PNG_FILTER_VALUE_SUB 129 
#define  PNG_FILTER_VALUE_UP 128 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  stub1 (int*,int*,int*,int) ; 
 int /*<<< orphan*/  sub_left_prediction (TYPE_2__*,int*,int*,int,int) ; 
 int /*<<< orphan*/  sub_png_paeth_prediction (int*,int*,int*,int,int) ; 

__attribute__((used)) static void png_filter_row(PNGEncContext *c, uint8_t *dst, int filter_type,
                           uint8_t *src, uint8_t *top, int size, int bpp)
{
    int i;

    switch (filter_type) {
    case PNG_FILTER_VALUE_NONE:
        memcpy(dst, src, size);
        break;
    case PNG_FILTER_VALUE_SUB:
        sub_left_prediction(c, dst, src, bpp, size);
        break;
    case PNG_FILTER_VALUE_UP:
        c->llvidencdsp.diff_bytes(dst, src, top, size);
        break;
    case PNG_FILTER_VALUE_AVG:
        for (i = 0; i < bpp; i++)
            dst[i] = src[i] - (top[i] >> 1);
        for (; i < size; i++)
            dst[i] = src[i] - ((src[i - bpp] + top[i]) >> 1);
        break;
    case PNG_FILTER_VALUE_PAETH:
        for (i = 0; i < bpp; i++)
            dst[i] = src[i] - top[i];
        sub_png_paeth_prediction(dst + i, src + i, top + i, size - i, bpp);
        break;
    }
}