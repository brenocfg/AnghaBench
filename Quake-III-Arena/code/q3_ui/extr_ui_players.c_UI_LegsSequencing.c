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
struct TYPE_5__ {int legsAnim; scalar_t__ legsAnimationTimer; } ;
typedef  TYPE_1__ playerInfo_t ;

/* Variables and functions */
 int ANIM_TOGGLEBIT ; 
 int JUMP_HEIGHT ; 
 int /*<<< orphan*/  LEGS_IDLE ; 
 int LEGS_JUMP ; 
 int LEGS_LAND ; 
 int M_PI ; 
 int /*<<< orphan*/  UI_ForceLegsAnim (TYPE_1__*,int) ; 
 int /*<<< orphan*/  UI_SetLegsAnim (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int UI_TIMER_JUMP ; 
 int UI_TIMER_LAND ; 
 int jumpHeight ; 
 int sin (int) ; 

__attribute__((used)) static void UI_LegsSequencing( playerInfo_t *pi ) {
	int		currentAnim;

	currentAnim = pi->legsAnim & ~ANIM_TOGGLEBIT;

	if ( pi->legsAnimationTimer > 0 ) {
		if ( currentAnim == LEGS_JUMP ) {
			jumpHeight = JUMP_HEIGHT * sin( M_PI * ( UI_TIMER_JUMP - pi->legsAnimationTimer ) / UI_TIMER_JUMP );
		}
		return;
	}

	if ( currentAnim == LEGS_JUMP ) {
		UI_ForceLegsAnim( pi, LEGS_LAND );
		pi->legsAnimationTimer = UI_TIMER_LAND;
		jumpHeight = 0;
		return;
	}

	if ( currentAnim == LEGS_LAND ) {
		UI_SetLegsAnim( pi, LEGS_IDLE );
		return;
	}
}