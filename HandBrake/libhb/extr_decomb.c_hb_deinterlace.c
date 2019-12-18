#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {TYPE_1__* plane; } ;
typedef  TYPE_2__ hb_buffer_t ;
struct TYPE_10__ {int* tap; int normalize; } ;
typedef  TYPE_3__ filter_param_t ;
struct TYPE_8__ {int width; int stride; int height_stride; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  blend_filter_line (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  fill_stride (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void hb_deinterlace(hb_buffer_t *dst, hb_buffer_t *src)
{
    int pp;
    filter_param_t filter;

    filter.tap[0] = -1;
    filter.tap[1] = 4;
    filter.tap[2] = 2;
    filter.tap[3] = 4;
    filter.tap[4] = -1;
    filter.normalize = 3;

    fill_stride(src);
    for (pp = 0; pp < 3; pp++)
    {
        int yy;
        int width  = src->plane[pp].width;
        int stride = src->plane[pp].stride;
        int height = src->plane[pp].height_stride;

        // Filter parity lines
        uint8_t *pdst = &dst->plane[pp].data[0];
        uint8_t *psrc = &src->plane[pp].data[0];

        /* These will be useful if we ever do temporal blending. */
        for( yy = 0; yy < height - 1; yy += 2 )
        {
            /* This line gets blend filtered, not yadif filtered. */
            memcpy(pdst, psrc, width);
            pdst += stride;
            psrc += stride;
            blend_filter_line(&filter, pdst, psrc, width, height, stride, yy + 1);
            pdst += stride;
            psrc += stride;
        }
    }
}