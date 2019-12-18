#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  nb_iterations; int /*<<< orphan*/  kernel; } ;
struct TYPE_5__ {TYPE_2__* priv; } ;
typedef  TYPE_1__ OCVContext ;
typedef  int /*<<< orphan*/  IplImage ;
typedef  TYPE_2__ DilateContext ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  cvDilate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dilate_end_frame_filter(AVFilterContext *ctx, IplImage *inimg, IplImage *outimg)
{
    OCVContext *s = ctx->priv;
    DilateContext *dilate = s->priv;
    cvDilate(inimg, outimg, dilate->kernel, dilate->nb_iterations);
}