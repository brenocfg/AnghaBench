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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int* linesize; int /*<<< orphan*/ ** data; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */

__attribute__((used)) static void get_frame_mb(const AVFrame *frame, int x, int y, uint8_t mb[], int dim)
{
    int i, j, cp;

    for (cp=0; cp<3; cp++) {
        int stride = frame->linesize[cp];
        for (i=0; i<dim; i++)
            for (j=0; j<dim; j++)
                *mb++ = frame->data[cp][(y+i)*stride + x + j];
    }
}