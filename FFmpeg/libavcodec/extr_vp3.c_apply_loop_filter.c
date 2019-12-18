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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ptrdiff_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* v_loop_filter ) (int /*<<< orphan*/ *,int,int*) ;int /*<<< orphan*/  (* h_loop_filter ) (int /*<<< orphan*/ *,int,int*) ;} ;
struct TYPE_8__ {TYPE_1__* f; } ;
struct TYPE_11__ {int* bounding_values_array; int* fragment_width; int* fragment_height; int* fragment_start; TYPE_4__ vp3dsp; TYPE_3__* all_fragments; scalar_t__* data_offset; int /*<<< orphan*/  flipped_image; TYPE_2__ current_frame; } ;
typedef  TYPE_5__ Vp3DecodeContext ;
struct TYPE_9__ {scalar_t__ coding_method; } ;
struct TYPE_7__ {int* linesize; int /*<<< orphan*/ ** data; } ;

/* Variables and functions */
 scalar_t__ MODE_COPY ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,int,int*) ; 

__attribute__((used)) static void apply_loop_filter(Vp3DecodeContext *s, int plane,
                              int ystart, int yend)
{
    int x, y;
    int *bounding_values = s->bounding_values_array + 127;

    int width           = s->fragment_width[!!plane];
    int height          = s->fragment_height[!!plane];
    int fragment        = s->fragment_start[plane] + ystart * width;
    ptrdiff_t stride    = s->current_frame.f->linesize[plane];
    uint8_t *plane_data = s->current_frame.f->data[plane];
    if (!s->flipped_image)
        stride = -stride;
    plane_data += s->data_offset[plane] + 8 * ystart * stride;

    for (y = ystart; y < yend; y++) {
        for (x = 0; x < width; x++) {
            /* This code basically just deblocks on the edges of coded blocks.
             * However, it has to be much more complicated because of the
             * brain damaged deblock ordering used in VP3/Theora. Order matters
             * because some pixels get filtered twice. */
            if (s->all_fragments[fragment].coding_method != MODE_COPY) {
                /* do not perform left edge filter for left columns frags */
                if (x > 0) {
                    s->vp3dsp.h_loop_filter(
                        plane_data + 8 * x,
                        stride, bounding_values);
                }

                /* do not perform top edge filter for top row fragments */
                if (y > 0) {
                    s->vp3dsp.v_loop_filter(
                        plane_data + 8 * x,
                        stride, bounding_values);
                }

                /* do not perform right edge filter for right column
                 * fragments or if right fragment neighbor is also coded
                 * in this frame (it will be filtered in next iteration) */
                if ((x < width - 1) &&
                    (s->all_fragments[fragment + 1].coding_method == MODE_COPY)) {
                    s->vp3dsp.h_loop_filter(
                        plane_data + 8 * x + 8,
                        stride, bounding_values);
                }

                /* do not perform bottom edge filter for bottom row
                 * fragments or if bottom fragment neighbor is also coded
                 * in this frame (it will be filtered in the next row) */
                if ((y < height - 1) &&
                    (s->all_fragments[fragment + width].coding_method == MODE_COPY)) {
                    s->vp3dsp.v_loop_filter(
                        plane_data + 8 * x + 8 * stride,
                        stride, bounding_values);
                }
            }

            fragment++;
        }
        plane_data += 8 * stride;
    }
}