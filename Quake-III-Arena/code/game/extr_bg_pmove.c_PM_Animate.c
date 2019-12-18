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
struct TYPE_4__ {int buttons; } ;
struct TYPE_6__ {TYPE_2__* ps; TYPE_1__ cmd; } ;
struct TYPE_5__ {int torsoTimer; } ;

/* Variables and functions */
 int BUTTON_AFFIRMATIVE ; 
 int BUTTON_FOLLOWME ; 
 int BUTTON_GESTURE ; 
 int BUTTON_GETFLAG ; 
 int BUTTON_GUARDBASE ; 
 int BUTTON_NEGATIVE ; 
 int BUTTON_PATROL ; 
 int /*<<< orphan*/  EV_TAUNT ; 
 int /*<<< orphan*/  PM_AddEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PM_StartTorsoAnim (int /*<<< orphan*/ ) ; 
 int TIMER_GESTURE ; 
 int /*<<< orphan*/  TORSO_AFFIRMATIVE ; 
 int /*<<< orphan*/  TORSO_FOLLOWME ; 
 int /*<<< orphan*/  TORSO_GESTURE ; 
 int /*<<< orphan*/  TORSO_GETFLAG ; 
 int /*<<< orphan*/  TORSO_GUARDBASE ; 
 int /*<<< orphan*/  TORSO_NEGATIVE ; 
 int /*<<< orphan*/  TORSO_PATROL ; 
 TYPE_3__* pm ; 

__attribute__((used)) static void PM_Animate( void ) {
	if ( pm->cmd.buttons & BUTTON_GESTURE ) {
		if ( pm->ps->torsoTimer == 0 ) {
			PM_StartTorsoAnim( TORSO_GESTURE );
			pm->ps->torsoTimer = TIMER_GESTURE;
			PM_AddEvent( EV_TAUNT );
		}
#ifdef MISSIONPACK
	} else if ( pm->cmd.buttons & BUTTON_GETFLAG ) {
		if ( pm->ps->torsoTimer == 0 ) {
			PM_StartTorsoAnim( TORSO_GETFLAG );
			pm->ps->torsoTimer = 600;	//TIMER_GESTURE;
		}
	} else if ( pm->cmd.buttons & BUTTON_GUARDBASE ) {
		if ( pm->ps->torsoTimer == 0 ) {
			PM_StartTorsoAnim( TORSO_GUARDBASE );
			pm->ps->torsoTimer = 600;	//TIMER_GESTURE;
		}
	} else if ( pm->cmd.buttons & BUTTON_PATROL ) {
		if ( pm->ps->torsoTimer == 0 ) {
			PM_StartTorsoAnim( TORSO_PATROL );
			pm->ps->torsoTimer = 600;	//TIMER_GESTURE;
		}
	} else if ( pm->cmd.buttons & BUTTON_FOLLOWME ) {
		if ( pm->ps->torsoTimer == 0 ) {
			PM_StartTorsoAnim( TORSO_FOLLOWME );
			pm->ps->torsoTimer = 600;	//TIMER_GESTURE;
		}
	} else if ( pm->cmd.buttons & BUTTON_AFFIRMATIVE ) {
		if ( pm->ps->torsoTimer == 0 ) {
			PM_StartTorsoAnim( TORSO_AFFIRMATIVE);
			pm->ps->torsoTimer = 600;	//TIMER_GESTURE;
		}
	} else if ( pm->cmd.buttons & BUTTON_NEGATIVE ) {
		if ( pm->ps->torsoTimer == 0 ) {
			PM_StartTorsoAnim( TORSO_NEGATIVE );
			pm->ps->torsoTimer = 600;	//TIMER_GESTURE;
		}
#endif
	}
}