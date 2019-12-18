#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  winktime; int /*<<< orphan*/  pots_winkstart; } ;
typedef  TYPE_1__ IXJ ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  PLD_SLIC_STATE_OC ; 
 int /*<<< orphan*/  SLIC_GetState (TYPE_1__*) ; 
 int /*<<< orphan*/  SLIC_SetState (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ixj_wink(IXJ *j)
{
	BYTE slicnow;

	slicnow = SLIC_GetState(j);

	j->pots_winkstart = jiffies;
	SLIC_SetState(PLD_SLIC_STATE_OC, j);

	msleep(jiffies_to_msecs(j->winktime));

	SLIC_SetState(slicnow, j);
	return 0;
}