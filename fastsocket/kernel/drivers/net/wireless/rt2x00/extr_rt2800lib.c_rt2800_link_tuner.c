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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00_dev {int dummy; } ;
struct link_qual {int rssi; } ;

/* Variables and functions */
 int /*<<< orphan*/  REV_RT2860C ; 
 int /*<<< orphan*/  RT2860 ; 
 int /*<<< orphan*/  RT5592 ; 
 int rt2800_get_default_vgc (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_set_vgc (struct rt2x00_dev*,struct link_qual*,int) ; 
 scalar_t__ rt2x00_rt (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00_rt_rev (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rt2800_link_tuner(struct rt2x00_dev *rt2x00dev, struct link_qual *qual,
		       const u32 count)
{
	u8 vgc;

	if (rt2x00_rt_rev(rt2x00dev, RT2860, REV_RT2860C))
		return;
	/*
	 * When RSSI is better then -80 increase VGC level with 0x10, except
	 * for rt5592 chip.
	 */

	vgc = rt2800_get_default_vgc(rt2x00dev);

	if (rt2x00_rt(rt2x00dev, RT5592) && qual->rssi > -65)
		vgc += 0x20;
	else if (qual->rssi > -80)
		vgc += 0x10;

	rt2800_set_vgc(rt2x00dev, qual, vgc);
}