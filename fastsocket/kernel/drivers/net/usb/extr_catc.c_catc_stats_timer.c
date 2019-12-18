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
struct catc {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 scalar_t__ EthStats ; 
 scalar_t__ STATS_UPDATE ; 
 int /*<<< orphan*/  catc_get_reg_async (struct catc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  catc_stats_done ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void catc_stats_timer(unsigned long data)
{
	struct catc *catc = (void *) data;
	int i;

	for (i = 0; i < 8; i++)
		catc_get_reg_async(catc, EthStats + 7 - i, catc_stats_done);

	mod_timer(&catc->timer, jiffies + STATS_UPDATE);
}