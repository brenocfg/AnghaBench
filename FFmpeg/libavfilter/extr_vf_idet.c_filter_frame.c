#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_12__ ;

/* Type definitions */
typedef  scalar_t__ ff_idet_filter_func ;
struct TYPE_23__ {int /*<<< orphan*/ * outputs; TYPE_1__** inputs; TYPE_3__* priv; } ;
struct TYPE_22__ {scalar_t__ w; scalar_t__ h; scalar_t__ format; TYPE_6__* dst; } ;
struct TYPE_21__ {scalar_t__ width; scalar_t__ height; scalar_t__ format; scalar_t__ interlaced_frame; } ;
struct TYPE_20__ {int analyze_interlaced_flag; int analyze_interlaced_flag_done; scalar_t__ interlaced_flag_accuracy; scalar_t__ last_type; TYPE_4__* cur; TYPE_4__* next; scalar_t__ filter_line; TYPE_12__* csp; TYPE_4__* prev; } ;
struct TYPE_19__ {int depth; } ;
struct TYPE_18__ {scalar_t__ format; scalar_t__ w; scalar_t__ h; } ;
struct TYPE_17__ {TYPE_2__* comp; } ;
typedef  TYPE_3__ IDETContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterLink ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 scalar_t__ ARCH_X86 ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ PROGRESSIVE ; 
 scalar_t__ UNDETERMINED ; 
 TYPE_4__* av_frame_clone (TYPE_4__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_4__**) ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 TYPE_12__* av_pix_fmt_desc_get (scalar_t__) ; 
 int ff_filter_frame (int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ ff_idet_filter_line_c_16bit ; 
 int /*<<< orphan*/  ff_idet_init_x86 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  filter (TYPE_6__*) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *link, AVFrame *picref)
{
    AVFilterContext *ctx = link->dst;
    IDETContext *idet = ctx->priv;

    // initial frame(s) and not interlaced, just pass through for
    // the analyze_interlaced_flag mode
    if (idet->analyze_interlaced_flag &&
        !picref->interlaced_frame &&
        !idet->next) {
        return ff_filter_frame(ctx->outputs[0], picref);
    }
    if (idet->analyze_interlaced_flag_done) {
        if (picref->interlaced_frame && idet->interlaced_flag_accuracy < 0)
            picref->interlaced_frame = 0;
        return ff_filter_frame(ctx->outputs[0], picref);
    }

    av_frame_free(&idet->prev);

    if(   picref->width  != link->w
       || picref->height != link->h
       || picref->format != link->format) {
        link->dst->inputs[0]->format = picref->format;
        link->dst->inputs[0]->w      = picref->width;
        link->dst->inputs[0]->h      = picref->height;

        av_frame_free(&idet->cur );
        av_frame_free(&idet->next);
    }

    idet->prev = idet->cur;
    idet->cur  = idet->next;
    idet->next = picref;

    if (!idet->cur &&
        !(idet->cur = av_frame_clone(idet->next)))
        return AVERROR(ENOMEM);

    if (!idet->prev)
        return 0;

    if (!idet->csp)
        idet->csp = av_pix_fmt_desc_get(link->format);
    if (idet->csp->comp[0].depth > 8){
        idet->filter_line = (ff_idet_filter_func)ff_idet_filter_line_c_16bit;
        if (ARCH_X86)
            ff_idet_init_x86(idet, 1);
    }

    if (idet->analyze_interlaced_flag) {
        if (idet->cur->interlaced_frame) {
            idet->cur->interlaced_frame = 0;
            filter(ctx);
            if (idet->last_type == PROGRESSIVE) {
                idet->interlaced_flag_accuracy --;
                idet->analyze_interlaced_flag --;
            } else if (idet->last_type != UNDETERMINED) {
                idet->interlaced_flag_accuracy ++;
                idet->analyze_interlaced_flag --;
            }
            if (idet->analyze_interlaced_flag == 1) {
                ff_filter_frame(ctx->outputs[0], av_frame_clone(idet->cur));

                if (idet->next->interlaced_frame && idet->interlaced_flag_accuracy < 0)
                    idet->next->interlaced_frame = 0;
                idet->analyze_interlaced_flag_done = 1;
                av_log(ctx, AV_LOG_INFO, "Final flag accuracy %d\n", idet->interlaced_flag_accuracy);
                return ff_filter_frame(ctx->outputs[0], av_frame_clone(idet->next));
            }
        }
    } else {
        filter(ctx);
    }

    return ff_filter_frame(ctx->outputs[0], av_frame_clone(idet->cur));
}