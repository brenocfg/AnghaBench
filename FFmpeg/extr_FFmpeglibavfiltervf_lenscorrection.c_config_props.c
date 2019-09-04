#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__** inputs; TYPE_1__* priv; } ;
struct TYPE_9__ {int /*<<< orphan*/  format; int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_4__* src; } ;
struct TYPE_8__ {int /*<<< orphan*/  log2_chroma_h; int /*<<< orphan*/  log2_chroma_w; } ;
struct TYPE_7__ {int /*<<< orphan*/  nb_planes; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  vsub; int /*<<< orphan*/  hsub; } ;
typedef  TYPE_1__ LenscorrectionCtx ;
typedef  TYPE_2__ AVPixFmtDescriptor ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_pix_fmt_count_planes (int /*<<< orphan*/ ) ; 
 TYPE_2__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_props(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    LenscorrectionCtx *rect = ctx->priv;
    AVFilterLink *inlink = ctx->inputs[0];
    const AVPixFmtDescriptor *pixdesc = av_pix_fmt_desc_get(inlink->format);
    rect->hsub = pixdesc->log2_chroma_w;
    rect->vsub = pixdesc->log2_chroma_h;
    outlink->w = rect->width = inlink->w;
    outlink->h = rect->height = inlink->h;
    rect->nb_planes = av_pix_fmt_count_planes(inlink->format);
    return 0;
}