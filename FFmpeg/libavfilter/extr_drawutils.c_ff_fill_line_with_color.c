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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  rgba_map ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_5__ {int log2_chroma_w; } ;
typedef  TYPE_1__ AVPixFmtDescriptor ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_CEIL_RSHIFT (int,int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 size_t RGB_TO_U_CCIR (size_t,size_t,size_t,int /*<<< orphan*/ ) ; 
 size_t RGB_TO_V_CCIR (size_t,size_t,size_t,int /*<<< orphan*/ ) ; 
 size_t RGB_TO_Y_CCIR (size_t,size_t,size_t) ; 
 int /*<<< orphan*/  av_assert0 (TYPE_1__ const*) ; 
 int /*<<< orphan*/  av_freep (size_t**) ; 
 int av_get_bits_per_pixel (TYPE_1__ const*) ; 
 size_t* av_malloc (int) ; 
 size_t* av_malloc_array (int,int) ; 
 TYPE_1__* av_pix_fmt_desc_get (int) ; 
 scalar_t__ ff_fill_rgba_map (size_t*,int) ; 
 int /*<<< orphan*/  memcpy (size_t*,size_t*,int) ; 
 int /*<<< orphan*/  memset (size_t*,size_t,int) ; 

int ff_fill_line_with_color(uint8_t *line[4], int pixel_step[4], int w, uint8_t dst_color[4],
                            enum AVPixelFormat pix_fmt, uint8_t rgba_color[4],
                            int *is_packed_rgba, uint8_t rgba_map_ptr[4])
{
    uint8_t rgba_map[4] = {0};
    int i;
    const AVPixFmtDescriptor *pix_desc = av_pix_fmt_desc_get(pix_fmt);
    int hsub;

    av_assert0(pix_desc);

    hsub = pix_desc->log2_chroma_w;

    *is_packed_rgba = ff_fill_rgba_map(rgba_map, pix_fmt) >= 0;

    if (*is_packed_rgba) {
        pixel_step[0] = (av_get_bits_per_pixel(pix_desc))>>3;
        for (i = 0; i < 4; i++)
            dst_color[rgba_map[i]] = rgba_color[i];

        line[0] = av_malloc_array(w, pixel_step[0]);
        if (!line[0])
            return AVERROR(ENOMEM);
        for (i = 0; i < w; i++)
            memcpy(line[0] + i * pixel_step[0], dst_color, pixel_step[0]);
        if (rgba_map_ptr)
            memcpy(rgba_map_ptr, rgba_map, sizeof(rgba_map[0]) * 4);
    } else {
        int plane;

        dst_color[0] = RGB_TO_Y_CCIR(rgba_color[0], rgba_color[1], rgba_color[2]);
        dst_color[1] = RGB_TO_U_CCIR(rgba_color[0], rgba_color[1], rgba_color[2], 0);
        dst_color[2] = RGB_TO_V_CCIR(rgba_color[0], rgba_color[1], rgba_color[2], 0);
        dst_color[3] = rgba_color[3];

        for (plane = 0; plane < 4; plane++) {
            int line_size;
            int hsub1 = (plane == 1 || plane == 2) ? hsub : 0;

            pixel_step[plane] = 1;
            line_size = AV_CEIL_RSHIFT(w, hsub1) * pixel_step[plane];
            line[plane] = av_malloc(line_size);
            if (!line[plane]) {
                while(plane && line[plane-1])
                    av_freep(&line[--plane]);
                return AVERROR(ENOMEM);
            }
            memset(line[plane], dst_color[plane], line_size);
        }
    }

    return 0;
}