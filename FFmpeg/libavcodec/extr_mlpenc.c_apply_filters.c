#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* cur_restart_header; } ;
struct TYPE_6__ {int min_channel; int max_channel; } ;
typedef  TYPE_1__ RestartHeader ;
typedef  TYPE_2__ MLPEncodeContext ;

/* Variables and functions */
 int /*<<< orphan*/  FIR ; 
 int /*<<< orphan*/  IIR ; 
 scalar_t__ apply_filter (TYPE_2__*,int) ; 
 int /*<<< orphan*/  set_filter_params (TYPE_2__*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void apply_filters(MLPEncodeContext *ctx)
{
    RestartHeader *rh = ctx->cur_restart_header;
    int channel;

    for (channel = rh->min_channel; channel <= rh->max_channel; channel++) {
        if (apply_filter(ctx, channel) < 0) {
            /* Filter is horribly wrong.
             * Clear filter params and update state. */
            set_filter_params(ctx, channel, FIR, 1);
            set_filter_params(ctx, channel, IIR, 1);
            apply_filter(ctx, channel);
        }
    }
}