#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  lfo_inc; int /*<<< orphan*/  eg_timer_add; } ;
struct TYPE_4__ {int /*<<< orphan*/  lfo_inc; int /*<<< orphan*/  eg_timer_add; } ;
struct TYPE_5__ {TYPE_1__ OPN; } ;

/* Variables and functions */
 TYPE_3__ crct ; 
 TYPE_2__ ym2612 ; 

__attribute__((used)) static void chan_render_prep(void)
{
	crct.eg_timer_add = ym2612.OPN.eg_timer_add;
	crct.lfo_inc = ym2612.OPN.lfo_inc;
}