#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint8_t ;
struct TYPE_13__ {scalar_t__* crop; } ;
typedef  TYPE_3__ hb_filter_private_t ;
struct TYPE_12__ {int width; int height; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_14__ {TYPE_2__ f; TYPE_1__* plane; } ;
typedef  TYPE_4__ hb_buffer_t ;
struct TYPE_15__ {int color; int w; int h; scalar_t__ dst_y; scalar_t__ dst_x; } ;
struct TYPE_11__ {unsigned int* data; int /*<<< orphan*/  stride; } ;
typedef  TYPE_5__ ASS_Image ;

/* Variables and functions */
 int /*<<< orphan*/  AV_PIX_FMT_YUVA420P ; 
 TYPE_4__* hb_frame_buffer_init (int /*<<< orphan*/ ,int,int) ; 
 int hb_rgb2yuv (unsigned int) ; 
 unsigned int ssaAlpha (TYPE_5__*,int,int) ; 

__attribute__((used)) static hb_buffer_t * RenderSSAFrame( hb_filter_private_t * pv, ASS_Image * frame )
{
    hb_buffer_t *sub;
    int xx, yy;

    unsigned r = ( frame->color >> 24 ) & 0xff;
    unsigned g = ( frame->color >> 16 ) & 0xff;
    unsigned b = ( frame->color >>  8 ) & 0xff;

    int yuv = hb_rgb2yuv((r << 16) | (g << 8) | b );

    unsigned frameY = (yuv >> 16) & 0xff;
    unsigned frameV = (yuv >> 8 ) & 0xff;
    unsigned frameU = (yuv >> 0 ) & 0xff;

    // Note that subtitle frame buffer is YUVA420P, not YUV420P, it has alpha
    sub = hb_frame_buffer_init(AV_PIX_FMT_YUVA420P, frame->w, frame->h);
    if (sub == NULL)
        return NULL;

    uint8_t *y_out, *u_out, *v_out, *a_out;
    y_out = sub->plane[0].data;
    u_out = sub->plane[1].data;
    v_out = sub->plane[2].data;
    a_out = sub->plane[3].data;

    for( yy = 0; yy < frame->h; yy++ )
    {
        for( xx = 0; xx < frame->w; xx++ )
        {
            y_out[xx] = frameY;
            if( ( yy & 1 ) == 0 )
            {
                u_out[xx>>1] = frameU;
                v_out[xx>>1] = frameV;
            }
            a_out[xx] = ssaAlpha( frame, xx, yy );;
        }
        y_out += sub->plane[0].stride;
        if( ( yy & 1 ) == 0 )
        {
            u_out += sub->plane[1].stride;
            v_out += sub->plane[2].stride;
        }
        a_out += sub->plane[3].stride;
    }
    sub->f.width = frame->w;
    sub->f.height = frame->h;
    sub->f.x = frame->dst_x + pv->crop[2];
    sub->f.y = frame->dst_y + pv->crop[0];

    return sub;
}