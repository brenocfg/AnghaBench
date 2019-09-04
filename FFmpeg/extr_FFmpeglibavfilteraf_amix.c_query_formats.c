#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* channel_layouts; } ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  int /*<<< orphan*/  AVFilterContext ;
typedef  TYPE_1__ AVFilterChannelLayouts ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_DBL ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_DBLP ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_FLT ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_FLTP ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 
 int ff_add_format (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 TYPE_1__* ff_all_channel_counts () ; 
 int /*<<< orphan*/  ff_all_samplerates () ; 
 int ff_set_common_channel_layouts (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int ff_set_common_formats (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ff_set_common_samplerates (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    AVFilterFormats *formats = NULL;
    AVFilterChannelLayouts *layouts;
    int ret;

    layouts = ff_all_channel_counts();
    if (!layouts) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    if ((ret = ff_add_format(&formats, AV_SAMPLE_FMT_FLT ))          < 0 ||
        (ret = ff_add_format(&formats, AV_SAMPLE_FMT_FLTP))          < 0 ||
        (ret = ff_add_format(&formats, AV_SAMPLE_FMT_DBL ))          < 0 ||
        (ret = ff_add_format(&formats, AV_SAMPLE_FMT_DBLP))          < 0 ||
        (ret = ff_set_common_formats        (ctx, formats))          < 0 ||
        (ret = ff_set_common_channel_layouts(ctx, layouts))          < 0 ||
        (ret = ff_set_common_samplerates(ctx, ff_all_samplerates())) < 0)
        goto fail;
    return 0;
fail:
    if (layouts)
        av_freep(&layouts->channel_layouts);
    av_freep(&layouts);
    return ret;
}