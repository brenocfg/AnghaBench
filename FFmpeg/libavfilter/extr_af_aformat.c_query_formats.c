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
struct TYPE_8__ {scalar_t__ channel_layouts; scalar_t__ sample_rates; scalar_t__ formats; } ;
struct TYPE_7__ {TYPE_2__* priv; } ;
typedef  TYPE_1__ AVFilterContext ;
typedef  TYPE_2__ AFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ ff_all_channel_counts () ; 
 scalar_t__ ff_all_formats (int /*<<< orphan*/ ) ; 
 scalar_t__ ff_all_samplerates () ; 
 int ff_set_common_channel_layouts (TYPE_1__*,scalar_t__) ; 
 int ff_set_common_formats (TYPE_1__*,scalar_t__) ; 
 int ff_set_common_samplerates (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    AFormatContext *s = ctx->priv;
    int ret;

    ret = ff_set_common_formats(ctx, s->formats ? s->formats :
                                            ff_all_formats(AVMEDIA_TYPE_AUDIO));
    if (ret < 0)
        return ret;
    ret = ff_set_common_samplerates(ctx, s->sample_rates ? s->sample_rates :
                                                     ff_all_samplerates());
    if (ret < 0)
        return ret;
    return ff_set_common_channel_layouts(ctx, s->channel_layouts ? s->channel_layouts :
                                                            ff_all_channel_counts());
}