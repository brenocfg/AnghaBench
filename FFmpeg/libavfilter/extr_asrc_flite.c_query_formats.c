#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_10__ {TYPE_2__* priv; } ;
struct TYPE_9__ {TYPE_1__* wave; } ;
struct TYPE_8__ {int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  num_channels; } ;
typedef  TYPE_2__ FliteContext ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  TYPE_3__ AVFilterContext ;
typedef  int /*<<< orphan*/  AVFilterChannelLayouts ;

/* Variables and functions */
 int /*<<< orphan*/  AV_SAMPLE_FMT_S16 ; 
 int /*<<< orphan*/  av_get_default_channel_layout (int /*<<< orphan*/ ) ; 
 int ff_add_channel_layout (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int ff_add_format (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int ff_set_common_channel_layouts (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int ff_set_common_formats (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int ff_set_common_samplerates (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    FliteContext *flite = ctx->priv;
    int ret;

    AVFilterChannelLayouts *chlayouts = NULL;
    int64_t chlayout = av_get_default_channel_layout(flite->wave->num_channels);
    AVFilterFormats *sample_formats = NULL;
    AVFilterFormats *sample_rates = NULL;

    if ((ret = ff_add_channel_layout         (&chlayouts     , chlayout                )) < 0 ||
        (ret = ff_set_common_channel_layouts (ctx            , chlayouts               )) < 0 ||
        (ret = ff_add_format                 (&sample_formats, AV_SAMPLE_FMT_S16       )) < 0 ||
        (ret = ff_set_common_formats         (ctx            , sample_formats          )) < 0 ||
        (ret = ff_add_format                 (&sample_rates  , flite->wave->sample_rate)) < 0 ||
        (ret = ff_set_common_samplerates     (ctx            , sample_rates            )) < 0)
        return ret;

    return 0;
}