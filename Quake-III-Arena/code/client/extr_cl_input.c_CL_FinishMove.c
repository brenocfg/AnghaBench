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
struct TYPE_4__ {int /*<<< orphan*/ * angles; int /*<<< orphan*/  serverTime; int /*<<< orphan*/  weapon; } ;
typedef  TYPE_1__ usercmd_t ;
struct TYPE_5__ {int /*<<< orphan*/ * viewangles; int /*<<< orphan*/  serverTime; int /*<<< orphan*/  cgameUserCmdValue; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANGLE2SHORT (int /*<<< orphan*/ ) ; 
 TYPE_2__ cl ; 

void CL_FinishMove( usercmd_t *cmd ) {
	int		i;

	// copy the state that the cgame is currently sending
	cmd->weapon = cl.cgameUserCmdValue;

	// send the current server time so the amount of movement
	// can be determined without allowing cheating
	cmd->serverTime = cl.serverTime;

	for (i=0 ; i<3 ; i++) {
		cmd->angles[i] = ANGLE2SHORT(cl.viewangles[i]);
	}
}