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
struct TYPE_6__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
typedef  TYPE_1__ ThreadData ;
struct TYPE_8__ {TYPE_2__* priv; } ;
struct TYPE_7__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_2__ OverlayContext ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  blend_slice_planar_rgb (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int blend_slice_gbrp_pm(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    OverlayContext *s = ctx->priv;
    ThreadData *td = arg;
    blend_slice_planar_rgb(ctx, td->dst, td->src, 0, 0, 0, s->x, s->y, 0, jobnr, nb_jobs);
    return 0;
}