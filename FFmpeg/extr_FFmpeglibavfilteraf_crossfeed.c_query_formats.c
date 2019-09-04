#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  int /*<<< orphan*/  AVFilterContext ;
typedef  int /*<<< orphan*/  AVFilterChannelLayouts ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CH_LAYOUT_STEREO ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_DBL ; 
 int ff_add_channel_layout (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int ff_add_format (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_all_samplerates () ; 
 int ff_set_common_channel_layouts (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ff_set_common_formats (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ff_set_common_samplerates (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    AVFilterFormats *formats = NULL;
    AVFilterChannelLayouts *layout = NULL;
    int ret;

    if ((ret = ff_add_format                 (&formats, AV_SAMPLE_FMT_DBL  )) < 0 ||
        (ret = ff_set_common_formats         (ctx     , formats            )) < 0 ||
        (ret = ff_add_channel_layout         (&layout , AV_CH_LAYOUT_STEREO)) < 0 ||
        (ret = ff_set_common_channel_layouts (ctx     , layout             )) < 0 ||
        (ret = ff_set_common_samplerates     (ctx     , ff_all_samplerates())) < 0)
        return ret;

    return 0;
}