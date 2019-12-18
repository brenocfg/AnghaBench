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
struct TYPE_8__ {int nb_inputs; TYPE_1__** inputs; } ;
struct TYPE_7__ {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  TYPE_2__ AVFilterContext ;
typedef  int /*<<< orphan*/  AVFilterChannelLayouts ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/ * ff_all_channel_counts () ; 
 int /*<<< orphan*/ * ff_all_formats (scalar_t__) ; 
 int /*<<< orphan*/ * ff_all_samplerates () ; 
 int ff_set_common_channel_layouts (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int ff_set_common_formats (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int ff_set_common_samplerates (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    AVFilterFormats *formats, *rates = NULL;
    AVFilterChannelLayouts *layouts = NULL;
    int ret, i;

    for (i = 0; i < ctx->nb_inputs; i++) {
        formats = ff_all_formats(ctx->inputs[i]->type);
        if ((ret = ff_set_common_formats(ctx, formats)) < 0)
            return ret;

        if (ctx->inputs[i]->type == AVMEDIA_TYPE_AUDIO) {
            rates = ff_all_samplerates();
            if ((ret = ff_set_common_samplerates(ctx, rates)) < 0)
                return ret;
            layouts = ff_all_channel_counts();
            if ((ret = ff_set_common_channel_layouts(ctx, layouts)) < 0)
                return ret;
        }
    }

    return 0;
}