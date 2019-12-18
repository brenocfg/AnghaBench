#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int qboolean ;
struct TYPE_5__ {scalar_t__ pm_type; } ;
struct TYPE_6__ {TYPE_1__ cur_ps; } ;
typedef  TYPE_2__ bot_state_t ;
struct TYPE_7__ {scalar_t__ intermissiontime; } ;

/* Variables and functions */
 scalar_t__ PM_FREEZE ; 
 scalar_t__ PM_INTERMISSION ; 
 TYPE_3__ level ; 
 int qtrue ; 

qboolean BotIntermission(bot_state_t *bs) {
	//NOTE: we shouldn't be looking at the game code...
	if (level.intermissiontime) return qtrue;
	return (bs->cur_ps.pm_type == PM_FREEZE || bs->cur_ps.pm_type == PM_INTERMISSION);
}