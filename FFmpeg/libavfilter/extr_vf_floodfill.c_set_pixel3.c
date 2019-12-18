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
struct TYPE_3__ {unsigned int** data; int* linesize; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */

__attribute__((used)) static void set_pixel3(AVFrame *frame, int x, int y,
                       unsigned d0, unsigned d1, unsigned d2, unsigned d3)
{
    frame->data[0][y * frame->linesize[0] + x] = d0;
    frame->data[1][y * frame->linesize[1] + x] = d1;
    frame->data[2][y * frame->linesize[2] + x] = d2;
}