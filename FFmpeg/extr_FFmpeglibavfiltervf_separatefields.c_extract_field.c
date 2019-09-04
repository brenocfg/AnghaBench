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
struct TYPE_3__ {int* linesize; scalar_t__* data; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */

__attribute__((used)) static void extract_field(AVFrame *frame, int nb_planes, int type)
{
    int i;

    for (i = 0; i < nb_planes; i++) {
        if (type)
            frame->data[i] = frame->data[i] + frame->linesize[i];
        frame->linesize[i] *= 2;
    }
}