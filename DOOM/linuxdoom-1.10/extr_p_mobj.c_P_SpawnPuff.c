#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int tics; int /*<<< orphan*/  momz; } ;
typedef  TYPE_1__ mobj_t ;
typedef  int fixed_t ;

/* Variables and functions */
 int /*<<< orphan*/  FRACUNIT ; 
 scalar_t__ MELEERANGE ; 
 int /*<<< orphan*/  MT_PUFF ; 
 int P_Random () ; 
 int /*<<< orphan*/  P_SetMobjState (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* P_SpawnMobj (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_PUFF3 ; 
 scalar_t__ attackrange ; 

void
P_SpawnPuff
( fixed_t	x,
  fixed_t	y,
  fixed_t	z )
{
    mobj_t*	th;
	
    z += ((P_Random()-P_Random())<<10);

    th = P_SpawnMobj (x,y,z, MT_PUFF);
    th->momz = FRACUNIT;
    th->tics -= P_Random()&3;

    if (th->tics < 1)
	th->tics = 1;
	
    // don't make punches spark on the wall
    if (attackrange == MELEERANGE)
	P_SetMobjState (th, S_PUFF3);
}