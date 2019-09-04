#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__** outputs; TYPE_1__** inputs; } ;
struct TYPE_4__ {int /*<<< orphan*/  in_channel_layouts; int /*<<< orphan*/  out_channel_layouts; int /*<<< orphan*/  in_samplerates; int /*<<< orphan*/  out_samplerates; int /*<<< orphan*/  in_formats; int /*<<< orphan*/  out_formats; } ;
typedef  TYPE_1__ AVFilterLink ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  TYPE_2__ AVFilterContext ;
typedef  int /*<<< orphan*/  AVFilterChannelLayouts ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * ff_all_channel_layouts () ; 
 int /*<<< orphan*/ * ff_all_formats (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ff_all_samplerates () ; 
 int ff_channel_layouts_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ff_formats_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    AVFilterLink *inlink  = ctx->inputs[0];
    AVFilterLink *outlink = ctx->outputs[0];
    AVFilterFormats *in_formats, *out_formats, *in_samplerates, *out_samplerates;
    AVFilterChannelLayouts *in_layouts, *out_layouts;
    int ret;

    if (!(in_formats      = ff_all_formats         (AVMEDIA_TYPE_AUDIO)) ||
        !(out_formats     = ff_all_formats         (AVMEDIA_TYPE_AUDIO)) ||
        !(in_samplerates  = ff_all_samplerates     (                  )) ||
        !(out_samplerates = ff_all_samplerates     (                  )) ||
        !(in_layouts      = ff_all_channel_layouts (                  )) ||
        !(out_layouts     = ff_all_channel_layouts (                  )))
        return AVERROR(ENOMEM);

    if ((ret = ff_formats_ref         (in_formats,      &inlink->out_formats        )) < 0 ||
        (ret = ff_formats_ref         (out_formats,     &outlink->in_formats        )) < 0 ||
        (ret = ff_formats_ref         (in_samplerates,  &inlink->out_samplerates    )) < 0 ||
        (ret = ff_formats_ref         (out_samplerates, &outlink->in_samplerates    )) < 0 ||
        (ret = ff_channel_layouts_ref (in_layouts,      &inlink->out_channel_layouts)) < 0 ||
        (ret = ff_channel_layouts_ref (out_layouts,     &outlink->in_channel_layouts)) < 0)
        return ret;

    return 0;
}