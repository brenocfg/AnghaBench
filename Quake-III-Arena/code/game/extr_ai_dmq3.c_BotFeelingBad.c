#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ weaponnum; int* inventory; } ;
typedef  TYPE_1__ bot_state_t ;

/* Variables and functions */
 size_t INVENTORY_HEALTH ; 
 scalar_t__ WP_GAUNTLET ; 
 scalar_t__ WP_MACHINEGUN ; 

float BotFeelingBad(bot_state_t *bs) {
	if (bs->weaponnum == WP_GAUNTLET) {
		return 100;
	}
	if (bs->inventory[INVENTORY_HEALTH] < 40) {
		return 100;
	}
	if (bs->weaponnum == WP_MACHINEGUN) {
		return 90;
	}
	if (bs->inventory[INVENTORY_HEALTH] < 60) {
		return 80;
	}
	return 0;
}