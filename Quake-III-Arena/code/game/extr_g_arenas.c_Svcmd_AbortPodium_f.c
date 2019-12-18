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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ integer; } ;
struct TYPE_5__ {int /*<<< orphan*/  time; } ;
struct TYPE_4__ {int /*<<< orphan*/  think; int /*<<< orphan*/  nextthink; } ;

/* Variables and functions */
 int /*<<< orphan*/  CelebrateStop ; 
 scalar_t__ GT_SINGLE_PLAYER ; 
 TYPE_3__ g_gametype ; 
 TYPE_2__ level ; 
 TYPE_1__* podium1 ; 

void Svcmd_AbortPodium_f( void ) {
	if( g_gametype.integer != GT_SINGLE_PLAYER ) {
		return;
	}

	if( podium1 ) {
		podium1->nextthink = level.time;
		podium1->think = CelebrateStop;
	}
}