#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int frame_size; TYPE_1__* avctx; } ;
typedef  TYPE_2__ XanContext ;
struct TYPE_8__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_6__ {int width; } ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static inline void xan_wc3_output_pixel_run(XanContext *s, AVFrame *frame,
    const uint8_t *pixel_buffer, int x, int y, int pixel_count)
{
    int stride;
    int line_inc;
    int index;
    int current_x;
    int width = s->avctx->width;
    uint8_t *palette_plane;

    palette_plane = frame->data[0];
    stride = frame->linesize[0];
    line_inc = stride - width;
    index = y * stride + x;
    current_x = x;
    while (pixel_count && index < s->frame_size) {
        int count = FFMIN(pixel_count, width - current_x);
        memcpy(palette_plane + index, pixel_buffer, count);
        pixel_count  -= count;
        index        += count;
        pixel_buffer += count;
        current_x    += count;

        if (current_x >= width) {
            index += line_inc;
            current_x = 0;
        }
    }
}