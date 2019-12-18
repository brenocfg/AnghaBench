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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int max_plane; int /*<<< orphan*/  height; int /*<<< orphan*/  fmt; int /*<<< orphan*/  width; } ;
struct TYPE_7__ {TYPE_2__* plane; TYPE_1__ f; int /*<<< orphan*/ * data; } ;
typedef  TYPE_3__ hb_buffer_t ;
struct TYPE_6__ {int stride; int height_stride; int size; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  hb_image_height (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int hb_image_height_stride (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int hb_image_stride (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hb_image_width (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void hb_buffer_init_planes(hb_buffer_t * b)
{
    uint8_t * data = b->data;
    int       pp;

    for( pp = 0; pp <= b->f.max_plane; pp++ )
    {
        b->plane[pp].data = data;
        b->plane[pp].stride        = hb_image_stride(b->f.fmt, b->f.width, pp);
        b->plane[pp].height_stride = hb_image_height_stride(b->f.fmt,
                                                            b->f.height, pp);
        b->plane[pp].width         = hb_image_width(b->f.fmt, b->f.width, pp);
        b->plane[pp].height        = hb_image_height(b->f.fmt, b->f.height, pp);
        b->plane[pp].size          = b->plane[pp].stride *
                                     b->plane[pp].height_stride;
        data                      += b->plane[pp].size;
    }
}