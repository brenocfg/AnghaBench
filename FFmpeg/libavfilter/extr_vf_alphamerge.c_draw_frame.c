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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {TYPE_1__* priv; } ;
struct TYPE_8__ {int height; int* linesize; int width; int /*<<< orphan*/ ** data; } ;
struct TYPE_7__ {int* rgba_map; scalar_t__ is_packed_rgb; } ;
typedef  TYPE_1__ AlphaMergeContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 size_t A ; 
 int /*<<< orphan*/  FFMIN (int const,int const) ; 
 size_t Y ; 
 int /*<<< orphan*/  av_image_copy_plane (int /*<<< orphan*/ *,int const,int /*<<< orphan*/ *,int const,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void draw_frame(AVFilterContext *ctx,
                       AVFrame *main_buf,
                       AVFrame *alpha_buf)
{
    AlphaMergeContext *s = ctx->priv;
    int h = main_buf->height;

    if (s->is_packed_rgb) {
        int x, y;
        uint8_t *pin, *pout;
        for (y = 0; y < h; y++) {
            pin = alpha_buf->data[0] + y * alpha_buf->linesize[0];
            pout = main_buf->data[0] + y * main_buf->linesize[0] + s->rgba_map[A];
            for (x = 0; x < main_buf->width; x++) {
                *pout = *pin;
                pin += 1;
                pout += 4;
            }
        }
    } else {
        const int main_linesize = main_buf->linesize[A];
        const int alpha_linesize = alpha_buf->linesize[Y];
        av_image_copy_plane(main_buf->data[A], main_linesize,
                            alpha_buf->data[Y], alpha_linesize,
                            FFMIN(main_linesize, alpha_linesize), alpha_buf->height);
    }
}