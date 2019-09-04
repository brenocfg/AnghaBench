#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;
struct TYPE_8__ {TYPE_1__* filter; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  TYPE_2__ AVFilterContext ;
typedef  int /*<<< orphan*/  AVFilterChannelLayouts ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_SAMPLE_FMT_DBLP 132 
#define  AV_SAMPLE_FMT_FLTP 131 
#define  AV_SAMPLE_FMT_NONE 130 
#define  AV_SAMPLE_FMT_S16P 129 
#define  AV_SAMPLE_FMT_S32P 128 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * ff_all_channel_counts () ; 
 int /*<<< orphan*/ * ff_all_samplerates () ; 
 int /*<<< orphan*/ * ff_make_format_list (int const*) ; 
 int ff_set_common_channel_layouts (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int ff_set_common_formats (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int ff_set_common_samplerates (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    AVFilterFormats *formats = NULL;
    AVFilterChannelLayouts *layouts = NULL;
    static const enum AVSampleFormat derivative_sample_fmts[] = {
        AV_SAMPLE_FMT_S16P, AV_SAMPLE_FMT_FLTP,
        AV_SAMPLE_FMT_S32P, AV_SAMPLE_FMT_DBLP,
        AV_SAMPLE_FMT_NONE
    };
    static const enum AVSampleFormat integral_sample_fmts[] = {
        AV_SAMPLE_FMT_FLTP, AV_SAMPLE_FMT_DBLP,
        AV_SAMPLE_FMT_NONE
    };
    int ret;

    formats = ff_make_format_list(strcmp(ctx->filter->name, "aintegral") ?
                                  derivative_sample_fmts : integral_sample_fmts);
    if (!formats)
        return AVERROR(ENOMEM);
    ret = ff_set_common_formats(ctx, formats);
    if (ret < 0)
        return ret;

    layouts = ff_all_channel_counts();
    if (!layouts)
        return AVERROR(ENOMEM);

    ret = ff_set_common_channel_layouts(ctx, layouts);
    if (ret < 0)
        return ret;

    formats = ff_all_samplerates();
    return ff_set_common_samplerates(ctx, formats);
}