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
typedef  int* vec3_t ;
typedef  int qboolean ;
struct TYPE_3__ {int /*<<< orphan*/  origin; } ;
typedef  TYPE_1__ bot_state_t ;

/* Variables and functions */
 int CONTENTS_LAVA ; 
 int CONTENTS_SLIME ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int*) ; 
 int trap_AAS_PointContents (int*) ; 

qboolean BotInLavaOrSlime(bot_state_t *bs) {
	vec3_t feet;

	VectorCopy(bs->origin, feet);
	feet[2] -= 23;
	return (trap_AAS_PointContents(feet) & (CONTENTS_LAVA|CONTENTS_SLIME));
}