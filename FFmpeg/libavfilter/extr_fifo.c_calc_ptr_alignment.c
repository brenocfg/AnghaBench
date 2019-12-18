#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int channels; scalar_t__* extended_data; int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 scalar_t__ av_sample_fmt_is_planar (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int calc_ptr_alignment(AVFrame *frame)
{
    int planes = av_sample_fmt_is_planar(frame->format) ?
                 frame->channels : 1;
    int min_align = 128;
    int p;

    for (p = 0; p < planes; p++) {
        int cur_align = 128;
        while ((intptr_t)frame->extended_data[p] % cur_align)
            cur_align >>= 1;
        if (cur_align < min_align)
            min_align = cur_align;
    }
    return min_align;
}