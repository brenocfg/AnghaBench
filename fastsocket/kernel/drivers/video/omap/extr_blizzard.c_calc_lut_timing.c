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
struct extif_timings {int clk_div; int cs_on_time; int we_on_time; int re_on_time; scalar_t__ we_off_time; int re_off_time; scalar_t__ we_cycle_time; int re_cycle_time; scalar_t__ cs_pulse_width; void* access_time; void* cs_off_time; } ;
struct TYPE_6__ {TYPE_2__* extif; TYPE_1__* fbdev; struct extif_timings lut_timings; int /*<<< orphan*/  extif_clk_period; } ;
struct TYPE_5__ {int (* convert_timings ) (struct extif_timings*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 TYPE_3__ blizzard ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long,scalar_t__,...) ; 
 int /*<<< orphan*/  memset (struct extif_timings*,int /*<<< orphan*/ ,int) ; 
 void* round_to_extif_ticks (int,int) ; 
 int stub1 (struct extif_timings*) ; 

__attribute__((used)) static int calc_lut_timing(unsigned long sysclk, int div)
{
	struct extif_timings *t;
	unsigned long systim;

	/* CSOnTime 0, WEOnTime 2 ns, REOnTime 2 ns,
	 * AccessTime 2 ns + 4 * SYSCLK + 26 (lut),
	 * WEOffTime = WEOnTime + 1 ns,
	 * REOffTime = REOnTime + 4*SYSCLK + 26 ns (lut),
	 * CSOffTime = REOffTime + 1 ns
	 * ReadCycle = 2ns + 4*SYSCLK + 26 ns (lut),
	 * WriteCycle = 2*SYSCLK + 2 ns,
	 * CSPulseWidth = 10 ns */

	systim = 1000000000 / (sysclk / 1000);
	dev_dbg(blizzard.fbdev->dev,
		"Blizzard systim %lu ps extif_clk_period %u div %d\n",
		systim, blizzard.extif_clk_period, div);

	t = &blizzard.lut_timings;
	memset(t, 0, sizeof(*t));

	t->clk_div = div;

	t->cs_on_time = 0;
	t->we_on_time = round_to_extif_ticks(t->cs_on_time + 2000, div);
	t->re_on_time = round_to_extif_ticks(t->cs_on_time + 2000, div);
	t->access_time = round_to_extif_ticks(t->re_on_time + 4 * systim +
					      26000, div);
	t->we_off_time = round_to_extif_ticks(t->we_on_time + 1000, div);
	t->re_off_time = round_to_extif_ticks(t->re_on_time + 4 * systim +
					      26000, div);
	t->cs_off_time = round_to_extif_ticks(t->re_off_time + 1000, div);
	t->we_cycle_time = round_to_extif_ticks(2 * systim + 2000, div);
	if (t->we_cycle_time < t->we_off_time)
		t->we_cycle_time = t->we_off_time;
	t->re_cycle_time = round_to_extif_ticks(2000 + 4 * systim + 26000, div);
	if (t->re_cycle_time < t->re_off_time)
		t->re_cycle_time = t->re_off_time;
	t->cs_pulse_width = 0;

	dev_dbg(blizzard.fbdev->dev,
		 "[lut]cson %d csoff %d reon %d reoff %d\n",
		 t->cs_on_time, t->cs_off_time, t->re_on_time, t->re_off_time);
	dev_dbg(blizzard.fbdev->dev,
		 "[lut]weon %d weoff %d recyc %d wecyc %d\n",
		 t->we_on_time, t->we_off_time, t->re_cycle_time,
		 t->we_cycle_time);
	dev_dbg(blizzard.fbdev->dev, "[lut]rdaccess %d cspulse %d\n",
		 t->access_time, t->cs_pulse_width);

	return blizzard.extif->convert_timings(t);
}