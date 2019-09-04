#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_5__ {int hsub; int vsub; int /*<<< orphan*/ * yuv_color; } ;
typedef  TYPE_1__ SignalstatsContext ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */

__attribute__((used)) static void burn_frame8(const SignalstatsContext *s, AVFrame *f, int x, int y)
{
    const int chromax = x >> s->hsub;
    const int chromay = y >> s->vsub;
    f->data[0][y       * f->linesize[0] +       x] = s->yuv_color[0];
    f->data[1][chromay * f->linesize[1] + chromax] = s->yuv_color[1];
    f->data[2][chromay * f->linesize[2] + chromax] = s->yuv_color[2];
}