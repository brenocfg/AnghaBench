#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ screen; scalar_t__ plan; int /*<<< orphan*/  eazmsn; void* si2; void* si1; int /*<<< orphan*/  phone; } ;
struct TYPE_6__ {TYPE_1__ setup; } ;
struct TYPE_7__ {TYPE_2__ parm; } ;
typedef  TYPE_3__ isdn_ctrl ;

/* Variables and functions */
 void* simple_strtoul (char*,int /*<<< orphan*/ *,int) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void
isdnloop_parse_setup(char *setup, isdn_ctrl * cmd)
{
	char *t = setup;
	char *s = strchr(t, ',');

	*s++ = '\0';
	strlcpy(cmd->parm.setup.phone, t, sizeof(cmd->parm.setup.phone));
	s = strchr(t = s, ',');
	*s++ = '\0';
	if (!strlen(t))
		cmd->parm.setup.si1 = 0;
	else
		cmd->parm.setup.si1 = simple_strtoul(t, NULL, 10);
	s = strchr(t = s, ',');
	*s++ = '\0';
	if (!strlen(t))
		cmd->parm.setup.si2 = 0;
	else
		cmd->parm.setup.si2 =
		    simple_strtoul(t, NULL, 10);
	strlcpy(cmd->parm.setup.eazmsn, s, sizeof(cmd->parm.setup.eazmsn));
	cmd->parm.setup.plan = 0;
	cmd->parm.setup.screen = 0;
}