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
struct TYPE_3__ {scalar_t__* inventory; int /*<<< orphan*/  lastair_time; int /*<<< orphan*/  eye; } ;
typedef  TYPE_1__ bot_state_t ;

/* Variables and functions */
 int CONTENTS_LAVA ; 
 int CONTENTS_SLIME ; 
 int CONTENTS_WATER ; 
 int /*<<< orphan*/  FloatTime () ; 
 size_t INVENTORY_ENVIRONMENTSUIT ; 
 int trap_AAS_PointContents (int /*<<< orphan*/ ) ; 

void BotCheckAir(bot_state_t *bs) {
	if (bs->inventory[INVENTORY_ENVIRONMENTSUIT] <= 0) {
		if (trap_AAS_PointContents(bs->eye) & (CONTENTS_WATER|CONTENTS_SLIME|CONTENTS_LAVA)) {
			return;
		}
	}
	bs->lastair_time = FloatTime();
}