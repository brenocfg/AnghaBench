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
typedef  int int64_t ;
struct TYPE_8__ {int channel_layout; int sample_rate; } ;
struct TYPE_7__ {TYPE_2__* priv; } ;
typedef  TYPE_1__ AVFilterContext ;
typedef  TYPE_2__ ANullContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  avfilter_make_format64_list (int*) ; 
 int /*<<< orphan*/  ff_all_formats (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_make_format_list (int*) ; 
 int ff_set_common_channel_layouts (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int ff_set_common_formats (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int ff_set_common_samplerates (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    ANullContext *null = ctx->priv;
    int64_t chlayouts[] = { null->channel_layout, -1 };
    int sample_rates[] = { null->sample_rate, -1 };
    int ret;

    if ((ret = ff_set_common_formats         (ctx, ff_all_formats              (AVMEDIA_TYPE_AUDIO))) < 0 ||
        (ret = ff_set_common_channel_layouts (ctx, avfilter_make_format64_list (chlayouts         ))) < 0 ||
        (ret = ff_set_common_samplerates     (ctx, ff_make_format_list         (sample_rates      ))) < 0)
        return ret;

    return 0;
}