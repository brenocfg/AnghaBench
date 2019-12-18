#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_11__ {int mask_box_x; int mask_box_y; int block_width; int block_height; int mode; TYPE_4__* mask; TYPE_2__* mask_filtered; } ;
typedef  TYPE_5__ hb_filter_private_t ;
struct TYPE_10__ {TYPE_3__* plane; } ;
struct TYPE_9__ {int* data; int stride; } ;
struct TYPE_8__ {TYPE_1__* plane; } ;
struct TYPE_7__ {int* data; int stride; } ;

/* Variables and functions */
 int MODE_FILTER ; 

__attribute__((used)) static void draw_mask_box( hb_filter_private_t * pv )
{
    int x = pv->mask_box_x;
    int y = pv->mask_box_y;
    int box_width = pv->block_width;
    int box_height = pv->block_height;
    int stride;
    uint8_t * mskp;

    if (pv->mode & MODE_FILTER)
    {
        mskp   = pv->mask_filtered->plane[0].data;
        stride = pv->mask_filtered->plane[0].stride;
    }
    else
    {
        mskp   = pv->mask->plane[0].data;
        stride = pv->mask->plane[0].stride;
    }


    int block_x, block_y;
    for (block_x = 0; block_x < box_width; block_x++)
    {
        mskp[ y               * stride + x + block_x] = 128;
        mskp[(y + box_height) * stride + x + block_x] = 128;
    }

    for (block_y = 0; block_y < box_height; block_y++)
    {
        mskp[stride * (y + block_y) + x            ] = 128;
        mskp[stride * (y + block_y) + x + box_width] = 128;
    }
}