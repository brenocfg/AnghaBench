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
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  p54u_free_urbs (struct ieee80211_hw*) ; 

__attribute__((used)) static void p54u_stop(struct ieee80211_hw *dev)
{
	/*
	 * TODO: figure out how to reliably stop the 3887 and net2280 so
	 * the hardware is still usable next time we want to start it.
	 * until then, we just stop listening to the hardware..
	 */
	p54u_free_urbs(dev);
}