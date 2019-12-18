#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint16_t ;

/* Variables and functions */
 int FFMIN (unsigned int,unsigned int) ; 

__attribute__((used)) static inline void subimage_with_fill_template(uint16_t *src, unsigned x, unsigned y,
                                               unsigned stride, unsigned width, unsigned height, uint16_t *dst,
                                               unsigned dst_width, unsigned dst_height, int is_alpha_plane,
                                               int is_interlaced, int is_top_field)
{
    int box_width = FFMIN(width - x, dst_width);
    int i, j, src_stride, box_height;
    uint16_t last_pix, *last_line;

    if (!is_interlaced) {
        src_stride = stride >> 1;
        src += y * src_stride + x;
        box_height = FFMIN(height - y, dst_height);
    } else {
        src_stride = stride; /* 2 lines stride */
        src += y * src_stride + x;
        box_height = FFMIN(height/2 - y, dst_height);
        if (!is_top_field)
            src += stride >> 1;
    }

    for (i = 0; i < box_height; ++i) {
        for (j = 0; j < box_width; ++j) {
            if (!is_alpha_plane) {
                dst[j] = src[j];
            } else {
                dst[j] = src[j] << 6; /* alpha 10b to 16b */
            }
        }
        if (!is_alpha_plane) {
            last_pix = dst[j - 1];
        } else {
            last_pix = dst[j - 1] << 6; /* alpha 10b to 16b */
        }
        for (; j < dst_width; j++)
            dst[j] = last_pix;
        src += src_stride;
        dst += dst_width;
    }
    last_line = dst - dst_width;
    for (; i < dst_height; i++) {
        for (j = 0; j < dst_width; ++j) {
            dst[j] = last_line[j];
        }
        dst += dst_width;
    }
}