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
struct TYPE_5__ {int control; } ;
typedef  TYPE_1__ hdcd_state ;
struct TYPE_6__ {scalar_t__ force_pe; } ;
typedef  TYPE_2__ HDCDContext ;

/* Variables and functions */

__attribute__((used)) static void hdcd_control(HDCDContext *ctx, hdcd_state *state, int *peak_extend, int *target_gain)
{
    *peak_extend = (ctx->force_pe || state->control & 16);
    *target_gain = (state->control & 15) << 7;
}