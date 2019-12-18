#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_12__ {int max_plane; int width; int height; int fmt; } ;
struct TYPE_11__ {int /*<<< orphan*/  type; } ;
struct TYPE_13__ {TYPE_3__ f; TYPE_2__ s; } ;
typedef  TYPE_4__ hb_buffer_t ;
struct TYPE_14__ {int nb_components; TYPE_1__* comp; } ;
struct TYPE_10__ {int plane; } ;
typedef  TYPE_5__ AVPixFmtDescriptor ;

/* Variables and functions */
 int /*<<< orphan*/  FRAME_BUF ; 
 TYPE_5__* av_pix_fmt_desc_get (int) ; 
 TYPE_4__* hb_buffer_init_internal (int) ; 
 int /*<<< orphan*/  hb_buffer_init_planes (TYPE_4__*) ; 
 int hb_image_height_stride (int,int,int) ; 
 int hb_image_stride (int,int,int) ; 

hb_buffer_t * hb_frame_buffer_init( int pix_fmt, int width, int height )
{
    const AVPixFmtDescriptor * desc = av_pix_fmt_desc_get(pix_fmt);
    hb_buffer_t              * buf;
    uint8_t                    has_plane[4] = {0,};
    int                        ii, pp, max_plane = 0;

    if (desc == NULL)
    {
        return NULL;
    }

    int size = 0;
    for (ii = 0; ii < desc->nb_components; ii++)
    {
        pp    = desc->comp[ii].plane;
        if (pp > max_plane)
        {
            max_plane = pp;
        }
        if (!has_plane[pp])
        {
            has_plane[pp] = 1;
            size += hb_image_stride( pix_fmt, width, pp ) *
                    hb_image_height_stride( pix_fmt, height, pp );
        }
    }

    buf = hb_buffer_init_internal(size);

    if( buf == NULL )
        return NULL;

    buf->f.max_plane = max_plane;
    buf->s.type = FRAME_BUF;
    buf->f.width = width;
    buf->f.height = height;
    buf->f.fmt = pix_fmt;

    hb_buffer_init_planes(buf);
    return buf;
}