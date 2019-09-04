#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* cur_restart_header; } ;
struct TYPE_5__ {int min_channel; int max_channel; } ;
typedef  TYPE_1__ RestartHeader ;
typedef  TYPE_2__ MLPEncodeContext ;

/* Variables and functions */
 int NUM_FILTERS ; 
 int /*<<< orphan*/  set_filter_params (TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void determine_filters(MLPEncodeContext *ctx)
{
    RestartHeader *rh = ctx->cur_restart_header;
    int channel, filter;

    for (channel = rh->min_channel; channel <= rh->max_channel; channel++) {
        for (filter = 0; filter < NUM_FILTERS; filter++)
            set_filter_params(ctx, channel, filter, 0);
    }
}