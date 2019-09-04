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
struct TYPE_10__ {int output_pads; TYPE_1__* priv; TYPE_3__** inputs; } ;
struct TYPE_9__ {int srcpad; void* w; void* h; int /*<<< orphan*/  format; TYPE_4__* src; } ;
struct TYPE_8__ {int /*<<< orphan*/  log2_chroma_w; int /*<<< orphan*/  log2_chroma_h; } ;
struct TYPE_7__ {int* map; } ;
typedef  TYPE_1__ ExtractPlanesContext ;
typedef  TYPE_2__ AVPixFmtDescriptor ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 void* AV_CEIL_RSHIFT (void*,int /*<<< orphan*/ ) ; 
 TYPE_2__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_output(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    AVFilterLink *inlink = ctx->inputs[0];
    ExtractPlanesContext *s = ctx->priv;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);
    const int output = outlink->srcpad - ctx->output_pads;

    if (s->map[output] == 1 || s->map[output] == 2) {
        outlink->h = AV_CEIL_RSHIFT(inlink->h, desc->log2_chroma_h);
        outlink->w = AV_CEIL_RSHIFT(inlink->w, desc->log2_chroma_w);
    }

    return 0;
}