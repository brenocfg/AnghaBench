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
struct TYPE_6__ {int* i_lines; int* i_stride; int* i_width; int in_sample_size; scalar_t__* img_planes; } ;
struct TYPE_7__ {TYPE_1__ img; } ;
typedef  TYPE_2__ xavs2_picture_t ;
struct TYPE_8__ {int* linesize; scalar_t__* data; } ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static void xavs2_copy_frame(xavs2_picture_t *pic, const AVFrame *frame)
{
    int j, k;
    for (k = 0; k < 3; k++) {
        for (j = 0; j < pic->img.i_lines[k]; j++) {
            memcpy( pic->img.img_planes[k] + pic->img.i_stride[k] * j,
                    frame->data[k]+frame->linesize[k] * j,
                    pic->img.i_width[k] * pic->img.in_sample_size);
        }
    }
}