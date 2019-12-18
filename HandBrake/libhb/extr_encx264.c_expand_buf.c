#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;
struct TYPE_7__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_9__ {TYPE_2__* plane; TYPE_1__ f; } ;
typedef  TYPE_3__ hb_buffer_t ;
struct TYPE_8__ {int height; int width; int stride; scalar_t__* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AV_PIX_FMT_YUV420P16BE ; 
 TYPE_3__* hb_frame_buffer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static hb_buffer_t * expand_buf(int bit_depth, hb_buffer_t *in)
{
    hb_buffer_t *buf;
    int          pp;
    int          shift = bit_depth - 8;

    buf = hb_frame_buffer_init(AV_PIX_FMT_YUV420P16BE,
                               in->f.width, in->f.height);
    for (pp = 0; pp < 3; pp++)
    {
        int       xx, yy;
        uint8_t  *src =  in->plane[pp].data;
        uint16_t *dst = (uint16_t*)buf->plane[pp].data;
        for (yy = 0; yy < in->plane[pp].height; yy++)
        {
            for (xx = 0; xx < in->plane[pp].width; xx++)
            {
                dst[xx] = (uint16_t)src[xx] << shift;
            }
            src +=  in->plane[pp].stride;
            dst += buf->plane[pp].stride / 2;
        }
    }
    return buf;
}