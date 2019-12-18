#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int torsoAnim; int /*<<< orphan*/  torsoAnimationTimer; } ;
typedef  TYPE_1__ playerInfo_t ;

/* Variables and functions */
 int ANIM_TOGGLEBIT ; 
 int TORSO_ATTACK ; 
 int TORSO_ATTACK2 ; 
 int TORSO_GESTURE ; 
 int /*<<< orphan*/  UI_TIMER_ATTACK ; 
 int /*<<< orphan*/  UI_TIMER_GESTURE ; 

__attribute__((used)) static void UI_ForceTorsoAnim( playerInfo_t *pi, int anim ) {
	pi->torsoAnim = ( ( pi->torsoAnim & ANIM_TOGGLEBIT ) ^ ANIM_TOGGLEBIT ) | anim;

	if ( anim == TORSO_GESTURE ) {
		pi->torsoAnimationTimer = UI_TIMER_GESTURE;
	}

	if ( anim == TORSO_ATTACK || anim == TORSO_ATTACK2 ) {
		pi->torsoAnimationTimer = UI_TIMER_ATTACK;
	}
}