#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  board; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCSR_BOARD_SD1PWR ; 
 int /*<<< orphan*/  au_sync_delay (int) ; 
 TYPE_1__* bcsr ; 

__attribute__((used)) static void pb1200mmc1_set_power(void *mmc_host, int state)
{
	if (state)
		bcsr->board |= BCSR_BOARD_SD1PWR;
	else
		bcsr->board &= ~BCSR_BOARD_SD1PWR;

	au_sync_delay(1);
}