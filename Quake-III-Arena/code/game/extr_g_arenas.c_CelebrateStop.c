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
struct TYPE_4__ {scalar_t__ weapon; int torsoAnim; } ;
struct TYPE_5__ {TYPE_1__ s; } ;
typedef  TYPE_2__ gentity_t ;

/* Variables and functions */
 int ANIM_TOGGLEBIT ; 
 int TORSO_STAND ; 
 int TORSO_STAND2 ; 
 scalar_t__ WP_GAUNTLET ; 

__attribute__((used)) static void CelebrateStop( gentity_t *player ) {
	int		anim;

	if( player->s.weapon == WP_GAUNTLET) {
		anim = TORSO_STAND2;
	}
	else {
		anim = TORSO_STAND;
	}
	player->s.torsoAnim = ( ( player->s.torsoAnim & ANIM_TOGGLEBIT ) ^ ANIM_TOGGLEBIT ) | anim;
}