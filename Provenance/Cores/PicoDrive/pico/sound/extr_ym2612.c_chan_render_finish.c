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
struct TYPE_6__ {int pack; int /*<<< orphan*/  lfo_cnt; int /*<<< orphan*/  eg_timer; int /*<<< orphan*/  eg_cnt; } ;
struct TYPE_4__ {int /*<<< orphan*/  lfo_cnt; int /*<<< orphan*/  eg_timer; int /*<<< orphan*/  eg_cnt; } ;
struct TYPE_5__ {TYPE_1__ OPN; } ;

/* Variables and functions */
 TYPE_3__ crct ; 
 int g_lfo_ampm ; 
 TYPE_2__ ym2612 ; 

__attribute__((used)) static void chan_render_finish(void)
{
	ym2612.OPN.eg_cnt = crct.eg_cnt;
	ym2612.OPN.eg_timer = crct.eg_timer;
	g_lfo_ampm = crct.pack >> 16; // need_save
	ym2612.OPN.lfo_cnt = crct.lfo_cnt;
}