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
typedef  float* vec4_t ;
struct TYPE_6__ {TYPE_2__* snap; } ;
struct TYPE_4__ {scalar_t__* persistant; } ;
struct TYPE_5__ {TYPE_1__ ps; } ;

/* Variables and functions */
 size_t PERS_TEAM ; 
 scalar_t__ TEAM_BLUE ; 
 scalar_t__ TEAM_RED ; 
 TYPE_3__ cg ; 

void CG_GetTeamColor(vec4_t *color) {
  if (cg.snap->ps.persistant[PERS_TEAM] == TEAM_RED) {
    (*color)[0] = 1.0f;
    (*color)[3] = 0.25f;
    (*color)[1] = (*color)[2] = 0.0f;
  } else if (cg.snap->ps.persistant[PERS_TEAM] == TEAM_BLUE) {
    (*color)[0] = (*color)[1] = 0.0f;
    (*color)[2] = 1.0f;
    (*color)[3] = 0.25f;
  } else {
    (*color)[0] = (*color)[2] = 0.0f;
    (*color)[1] = 0.17f;
    (*color)[3] = 0.25f;
	}
}