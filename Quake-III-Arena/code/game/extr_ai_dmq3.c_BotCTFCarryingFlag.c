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
struct TYPE_3__ {scalar_t__* inventory; } ;
typedef  TYPE_1__ bot_state_t ;

/* Variables and functions */
 int CTF_FLAG_BLUE ; 
 int CTF_FLAG_NONE ; 
 int CTF_FLAG_RED ; 
 scalar_t__ GT_CTF ; 
 size_t INVENTORY_BLUEFLAG ; 
 size_t INVENTORY_REDFLAG ; 
 scalar_t__ gametype ; 

int BotCTFCarryingFlag(bot_state_t *bs) {
	if (gametype != GT_CTF) return CTF_FLAG_NONE;

	if (bs->inventory[INVENTORY_REDFLAG] > 0) return CTF_FLAG_RED;
	else if (bs->inventory[INVENTORY_BLUEFLAG] > 0) return CTF_FLAG_BLUE;
	return CTF_FLAG_NONE;
}