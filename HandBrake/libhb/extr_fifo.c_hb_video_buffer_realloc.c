#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_10__ {int max_plane; int width; int height; int /*<<< orphan*/  fmt; } ;
struct TYPE_11__ {int size; TYPE_2__ f; } ;
typedef  TYPE_3__ hb_buffer_t ;
struct TYPE_12__ {int nb_components; TYPE_1__* comp; } ;
struct TYPE_9__ {int plane; } ;
typedef  TYPE_4__ AVPixFmtDescriptor ;

/* Variables and functions */
 TYPE_4__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_buffer_init_planes (TYPE_3__*) ; 
 int /*<<< orphan*/  hb_buffer_realloc (TYPE_3__*,int) ; 
 int hb_image_height_stride (int /*<<< orphan*/ ,int,int) ; 
 int hb_image_stride (int /*<<< orphan*/ ,int,int) ; 

void hb_video_buffer_realloc( hb_buffer_t * buf, int width, int height )
{
    const AVPixFmtDescriptor * desc = av_pix_fmt_desc_get(buf->f.fmt);
    uint8_t                    has_plane[4] = {0,};
    int                        ii, pp;

    if (desc == NULL)
    {
        return;
    }

    buf->f.max_plane = 0;
    int size = 0;
    for (ii = 0; ii < desc->nb_components; ii++)
    {
        pp = desc->comp[ii].plane;
        if (pp > buf->f.max_plane)
        {
            buf->f.max_plane = pp;
        }
        if (!has_plane[pp])
        {
            has_plane[pp] = 1;
            size += hb_image_stride(buf->f.fmt, width, pp) *
                    hb_image_height_stride(buf->f.fmt, height, pp );
        }
    }

    hb_buffer_realloc(buf, size );

    buf->f.width = width;
    buf->f.height = height;
    buf->size = size;

    hb_buffer_init_planes(buf);
}