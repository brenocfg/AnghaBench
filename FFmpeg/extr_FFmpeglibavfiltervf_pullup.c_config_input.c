#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* priv; } ;
struct TYPE_12__ {int h; int w; int /*<<< orphan*/  format; TYPE_4__* dst; } ;
struct TYPE_11__ {int /*<<< orphan*/  log2_chroma_w; int /*<<< orphan*/  log2_chroma_h; } ;
struct TYPE_10__ {int metric_plane; int nb_planes; int* planeheight; int* planewidth; int metric_w; int junk_left; int junk_right; int metric_h; int junk_top; int junk_bottom; int metric_offset; int metric_length; int /*<<< orphan*/  var; int /*<<< orphan*/  comb; int /*<<< orphan*/  diff; int /*<<< orphan*/  head; } ;
typedef  TYPE_1__ PullupContext ;
typedef  TYPE_2__ AVPixFmtDescriptor ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 scalar_t__ ARCH_X86 ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 void* AV_CEIL_RSHIFT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 int av_pix_fmt_count_planes (int /*<<< orphan*/ ) ; 
 TYPE_2__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comb_c ; 
 int /*<<< orphan*/  diff_c ; 
 int /*<<< orphan*/  ff_pullup_init_x86 (TYPE_1__*) ; 
 int /*<<< orphan*/  make_field_queue (TYPE_1__*,int) ; 
 int /*<<< orphan*/  var_c ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    PullupContext *s = ctx->priv;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);
    int mp = s->metric_plane;

    s->nb_planes = av_pix_fmt_count_planes(inlink->format);

    if (mp + 1 > s->nb_planes) {
        av_log(ctx, AV_LOG_ERROR, "input format does not have such plane\n");
        return AVERROR(EINVAL);
    }

    s->planeheight[1] = s->planeheight[2] = AV_CEIL_RSHIFT(inlink->h, desc->log2_chroma_h);
    s->planeheight[0] = s->planeheight[3] = inlink->h;
    s->planewidth[1]  = s->planewidth[2]  = AV_CEIL_RSHIFT(inlink->w, desc->log2_chroma_w);
    s->planewidth[0]  = s->planewidth[3]  = inlink->w;

    s->metric_w      = (s->planewidth[mp]  - ((s->junk_left + s->junk_right)  << 3)) >> 3;
    s->metric_h      = (s->planeheight[mp] - ((s->junk_top  + s->junk_bottom) << 1)) >> 3;
    s->metric_offset = (s->junk_left << 3) + (s->junk_top << 1) * s->planewidth[mp];
    s->metric_length = s->metric_w * s->metric_h;

    av_log(ctx, AV_LOG_DEBUG, "w: %d h: %d\n", s->metric_w, s->metric_h);
    av_log(ctx, AV_LOG_DEBUG, "offset: %d length: %d\n", s->metric_offset, s->metric_length);

    s->head = make_field_queue(s, 8);
    if (!s->head)
        return AVERROR(ENOMEM);

    s->diff = diff_c;
    s->comb = comb_c;
    s->var  = var_c;

    if (ARCH_X86)
        ff_pullup_init_x86(s);
    return 0;
}