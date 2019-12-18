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
struct TYPE_6__ {int* i_stride; int* i_lines; int* i_width; int /*<<< orphan*/ ** img_planes; } ;
struct TYPE_7__ {TYPE_1__ img; } ;
typedef  TYPE_2__ xavs2_picture_t ;
typedef  int const uint8_t ;
typedef  int uint16_t ;
struct TYPE_8__ {int** data; int* linesize; } ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xavs2_copy_frame_with_shift(xavs2_picture_t *pic, const AVFrame *frame, const int shift_in)
{
    int j, k;
    for (k = 0; k < 3; k++) {
        int i_stride = pic->img.i_stride[k];
        for (j = 0; j < pic->img.i_lines[k]; j++) {
            uint16_t *p_plane = (uint16_t *)&pic->img.img_planes[k][j * i_stride];
            int i;
            uint8_t *p_buffer = frame->data[k] + frame->linesize[k] * j;
            memset(p_plane, 0, i_stride);
            for (i = 0; i < pic->img.i_width[k]; i++) {
                p_plane[i] = p_buffer[i] << shift_in;
            }
        }
    }
}