#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* subsector; } ;
typedef  TYPE_2__ mobj_t ;
struct TYPE_6__ {int /*<<< orphan*/  sector; } ;

/* Variables and functions */
 int /*<<< orphan*/  P_RecursiveSound (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* soundtarget ; 
 int /*<<< orphan*/  validcount ; 

void
P_NoiseAlert
( mobj_t*	target,
  mobj_t*	emmiter )
{
    soundtarget = target;
    validcount++;
    P_RecursiveSound (emmiter->subsector->sector, 0);
}