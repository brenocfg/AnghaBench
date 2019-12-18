#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/ * cmdlist ; 
 int /*<<< orphan*/ * deletelist ; 
 int /*<<< orphan*/ * disablelist ; 
 int /*<<< orphan*/ * enablebreaklist ; 
 int /*<<< orphan*/ * enablelist ; 
 int /*<<< orphan*/ * infolist ; 
 int /*<<< orphan*/ * maintenanceinfolist ; 
 int /*<<< orphan*/ * maintenancelist ; 
 int /*<<< orphan*/ * maintenanceprintlist ; 
 int max_user_call_depth ; 
 int /*<<< orphan*/ * setchecklist ; 
 int /*<<< orphan*/ * sethistlist ; 
 int /*<<< orphan*/ * setlist ; 
 int /*<<< orphan*/ * setprintlist ; 
 int /*<<< orphan*/ * showchecklist ; 
 int /*<<< orphan*/ * showhistlist ; 
 int /*<<< orphan*/ * showlist ; 
 int /*<<< orphan*/ * showprintlist ; 
 int /*<<< orphan*/ * stoplist ; 
 int /*<<< orphan*/ * togglelist ; 
 int /*<<< orphan*/ * unsethistlist ; 
 int /*<<< orphan*/ * unsetlist ; 

void
init_cmd_lists (void)
{
  max_user_call_depth = 1024;

  cmdlist = NULL;
  infolist = NULL;
  enablelist = NULL;
  disablelist = NULL;
  togglelist = NULL;
  stoplist = NULL;
  deletelist = NULL;
  enablebreaklist = NULL;
  setlist = NULL;
  unsetlist = NULL;
  showlist = NULL;
  sethistlist = NULL;
  showhistlist = NULL;
  unsethistlist = NULL;
  maintenancelist = NULL;
  maintenanceinfolist = NULL;
  maintenanceprintlist = NULL;
  setprintlist = NULL;
  showprintlist = NULL;
  setchecklist = NULL;
  showchecklist = NULL;
}