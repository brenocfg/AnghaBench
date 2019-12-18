#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sample_rate; } ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  int /*<<< orphan*/  AVFilterContext ;
typedef  int /*<<< orphan*/  AVFilterChannelLayouts ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CH_LAYOUT_STEREO ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_FLT ; 
 int FF_ARRAY_ELEMS (TYPE_1__*) ; 
 int ff_add_channel_layout (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int ff_add_format (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int ff_set_common_channel_layouts (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ff_set_common_formats (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ff_set_common_samplerates (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* freqinfos ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    AVFilterFormats *formats = NULL;
    AVFilterChannelLayouts *layout = NULL;
    int i, ret;

    if ((ret = ff_add_format                 (&formats, AV_SAMPLE_FMT_FLT  )) < 0 ||
        (ret = ff_set_common_formats         (ctx     , formats            )) < 0 ||
        (ret = ff_add_channel_layout         (&layout , AV_CH_LAYOUT_STEREO)) < 0 ||
        (ret = ff_set_common_channel_layouts (ctx     , layout             )) < 0)
        return ret;

    formats = NULL;
    for (i = 0; i < FF_ARRAY_ELEMS(freqinfos); i++) {
        if ((ret = ff_add_format(&formats, freqinfos[i].sample_rate)) < 0)
            return ret;
    }

    return ff_set_common_samplerates(ctx, formats);
}