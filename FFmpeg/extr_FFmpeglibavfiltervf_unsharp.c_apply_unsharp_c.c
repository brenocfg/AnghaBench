#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UnsharpFilterParam ;
struct TYPE_8__ {int /*<<< orphan*/  chroma; int /*<<< orphan*/  luma; int /*<<< orphan*/  vsub; int /*<<< orphan*/  hsub; } ;
typedef  TYPE_1__ UnsharpContext ;
struct TYPE_11__ {TYPE_1__* priv; TYPE_3__** inputs; } ;
struct TYPE_10__ {int w; int h; } ;
struct TYPE_9__ {int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AV_CEIL_RSHIFT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apply_unsharp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int apply_unsharp_c(AVFilterContext *ctx, AVFrame *in, AVFrame *out)
{
    AVFilterLink *inlink = ctx->inputs[0];
    UnsharpContext *s = ctx->priv;
    int i, plane_w[3], plane_h[3];
    UnsharpFilterParam *fp[3];
    plane_w[0] = inlink->w;
    plane_w[1] = plane_w[2] = AV_CEIL_RSHIFT(inlink->w, s->hsub);
    plane_h[0] = inlink->h;
    plane_h[1] = plane_h[2] = AV_CEIL_RSHIFT(inlink->h, s->vsub);
    fp[0] = &s->luma;
    fp[1] = fp[2] = &s->chroma;
    for (i = 0; i < 3; i++) {
        apply_unsharp(out->data[i], out->linesize[i], in->data[i], in->linesize[i], plane_w[i], plane_h[i], fp[i]);
    }
    return 0;
}