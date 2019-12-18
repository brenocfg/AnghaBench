#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {float nextthink; int /*<<< orphan*/  (* think ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ gentity_t ;
struct TYPE_6__ {float time; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_Error (char*) ; 
 TYPE_3__ level ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void G_RunThink (gentity_t *ent) {
	float	thinktime;

	thinktime = ent->nextthink;
	if (thinktime <= 0) {
		return;
	}
	if (thinktime > level.time) {
		return;
	}
	
	ent->nextthink = 0;
	if (!ent->think) {
		G_Error ( "NULL ent->think");
	}
	ent->think (ent);
}