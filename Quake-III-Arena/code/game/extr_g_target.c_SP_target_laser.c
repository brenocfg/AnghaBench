#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ nextthink; int /*<<< orphan*/  think; } ;
typedef  TYPE_1__ gentity_t ;
struct TYPE_5__ {scalar_t__ time; } ;

/* Variables and functions */
 scalar_t__ FRAMETIME ; 
 TYPE_2__ level ; 
 int /*<<< orphan*/  target_laser_start ; 

void SP_target_laser (gentity_t *self)
{
	// let everything else get spawned before we start firing
	self->think = target_laser_start;
	self->nextthink = level.time + FRAMETIME;
}