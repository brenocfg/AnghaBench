#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {int frame_size; TYPE_6__* avctx; TYPE_1__* last_frame; } ;
typedef  TYPE_2__ XanContext ;
struct TYPE_10__ {int width; int height; } ;
struct TYPE_9__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_7__ {int /*<<< orphan*/ ** data; } ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
 int FFABS (int) ; 
 int FFMIN3 (int,int,int) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void xan_wc3_copy_pixel_run(XanContext *s, AVFrame *frame,
                                          int x, int y,
                                          int pixel_count, int motion_x,
                                          int motion_y)
{
    int stride;
    int line_inc;
    int curframe_index, prevframe_index;
    int curframe_x, prevframe_x;
    int width = s->avctx->width;
    uint8_t *palette_plane, *prev_palette_plane;

    if (y + motion_y < 0 || y + motion_y >= s->avctx->height ||
        x + motion_x < 0 || x + motion_x >= s->avctx->width)
        return;

    palette_plane = frame->data[0];
    prev_palette_plane = s->last_frame->data[0];
    if (!prev_palette_plane)
        prev_palette_plane = palette_plane;
    stride = frame->linesize[0];
    line_inc = stride - width;
    curframe_index = y * stride + x;
    curframe_x = x;
    prevframe_index = (y + motion_y) * stride + x + motion_x;
    prevframe_x = x + motion_x;

    if (prev_palette_plane == palette_plane && FFABS(motion_x + width*motion_y) < pixel_count) {
         avpriv_request_sample(s->avctx, "Overlapping copy");
         return ;
    }

    while (pixel_count &&
           curframe_index  < s->frame_size &&
           prevframe_index < s->frame_size) {
        int count = FFMIN3(pixel_count, width - curframe_x,
                           width - prevframe_x);

        memcpy(palette_plane + curframe_index,
               prev_palette_plane + prevframe_index, count);
        pixel_count     -= count;
        curframe_index  += count;
        prevframe_index += count;
        curframe_x      += count;
        prevframe_x     += count;

        if (curframe_x >= width) {
            curframe_index += line_inc;
            curframe_x = 0;
        }

        if (prevframe_x >= width) {
            prevframe_index += line_inc;
            prevframe_x = 0;
        }
    }
}