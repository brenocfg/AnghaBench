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
typedef  int /*<<< orphan*/  u32 ;
struct ssb_extif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSB_EXTIF_WATCHDOG ; 
 int /*<<< orphan*/  extif_write32 (struct ssb_extif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ssb_extif_watchdog_timer_set(struct ssb_extif *extif,
				  u32 ticks)
{
	extif_write32(extif, SSB_EXTIF_WATCHDOG, ticks);
}