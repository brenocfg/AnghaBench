#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int eventHandling; } ;

/* Variables and functions */
 int CGAME_EVENT_NONE ; 
 int CGAME_EVENT_SCOREBOARD ; 
 int CGAME_EVENT_TEAMMENU ; 
 int /*<<< orphan*/  CG_HideTeamMenu () ; 
 TYPE_1__ cgs ; 

void CG_EventHandling(int type) {
	cgs.eventHandling = type;
  if (type == CGAME_EVENT_NONE) {
    CG_HideTeamMenu();
  } else if (type == CGAME_EVENT_TEAMMENU) {
    //CG_ShowTeamMenu();
  } else if (type == CGAME_EVENT_SCOREBOARD) {
  }

}