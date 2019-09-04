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
typedef  int /*<<< orphan*/  AVFilterContext ;
typedef  int /*<<< orphan*/  AVFilterChannelLayouts ;

/* Variables and functions */
 int /*<<< orphan*/  SET_COMMON_FORMATS (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  channel_layouts ; 
 int /*<<< orphan*/  ff_channel_layouts_ref ; 
 int /*<<< orphan*/  ff_channel_layouts_unref ; 
 int /*<<< orphan*/  in_channel_layouts ; 
 int /*<<< orphan*/  out_channel_layouts ; 

int ff_set_common_channel_layouts(AVFilterContext *ctx,
                                  AVFilterChannelLayouts *layouts)
{
    SET_COMMON_FORMATS(ctx, layouts, in_channel_layouts, out_channel_layouts,
                       ff_channel_layouts_ref, ff_channel_layouts_unref, channel_layouts);
}