#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
struct TYPE_18__ {char* statstr; int action; void* command; } ;
typedef  TYPE_4__ isdnloop_stat ;
struct TYPE_17__ {int /*<<< orphan*/  (* statcallb ) (TYPE_6__*) ;} ;
struct TYPE_19__ {int myid; TYPE_3__ interface; int /*<<< orphan*/  flags; } ;
typedef  TYPE_5__ isdnloop_card ;
struct TYPE_15__ {int si1; int /*<<< orphan*/  screen; int /*<<< orphan*/  plan; int /*<<< orphan*/  si2; int /*<<< orphan*/  eazmsn; int /*<<< orphan*/  phone; } ;
struct TYPE_16__ {int /*<<< orphan*/  num; TYPE_1__ setup; } ;
struct TYPE_20__ {int driver; int arg; void* command; TYPE_2__ parm; } ;
typedef  TYPE_6__ isdn_ctrl ;

/* Variables and functions */
 int /*<<< orphan*/  ISDNLOOP_FLAGS_B1ACTIVE ; 
 int /*<<< orphan*/  ISDNLOOP_FLAGS_B2ACTIVE ; 
 void* ISDN_STAT_BHUP ; 
 void* ISDN_STAT_DHUP ; 
 int /*<<< orphan*/  isdnloop_free_queue (TYPE_5__*,int) ; 
 int /*<<< orphan*/  isdnloop_parse_setup (char*,TYPE_6__*) ; 
 TYPE_4__* isdnloop_stat_table ; 
 scalar_t__ simple_strtoul (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_6__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_6__*) ; 

__attribute__((used)) static void
isdnloop_parse_status(u_char * status, int channel, isdnloop_card * card)
{
	isdnloop_stat *s = isdnloop_stat_table;
	int action = -1;
	isdn_ctrl cmd;

	while (s->statstr) {
		if (!strncmp(status, s->statstr, strlen(s->statstr))) {
			cmd.command = s->command;
			action = s->action;
			break;
		}
		s++;
	}
	if (action == -1)
		return;
	cmd.driver = card->myid;
	cmd.arg = channel;
	switch (action) {
		case 1:
			/* BCON_x */
			card->flags |= (channel) ?
			    ISDNLOOP_FLAGS_B2ACTIVE : ISDNLOOP_FLAGS_B1ACTIVE;
			break;
		case 2:
			/* BDIS_x */
			card->flags &= ~((channel) ?
					 ISDNLOOP_FLAGS_B2ACTIVE : ISDNLOOP_FLAGS_B1ACTIVE);
			isdnloop_free_queue(card, channel);
			break;
		case 3:
			/* DCAL_I and DSCA_I */
			isdnloop_parse_setup(status + 6, &cmd);
			break;
		case 4:
			/* FCALL */
			sprintf(cmd.parm.setup.phone, "LEASED%d", card->myid);
			sprintf(cmd.parm.setup.eazmsn, "%d", channel + 1);
			cmd.parm.setup.si1 = 7;
			cmd.parm.setup.si2 = 0;
			cmd.parm.setup.plan = 0;
			cmd.parm.setup.screen = 0;
			break;
		case 5:
			/* CIF */
			strlcpy(cmd.parm.num, status + 3, sizeof(cmd.parm.num));
			break;
		case 6:
			/* AOC */
			snprintf(cmd.parm.num, sizeof(cmd.parm.num), "%d",
			     (int) simple_strtoul(status + 7, NULL, 16));
			break;
		case 7:
			/* CAU */
			status += 3;
			if (strlen(status) == 4)
				snprintf(cmd.parm.num, sizeof(cmd.parm.num), "%s%c%c",
				     status + 2, *status, *(status + 1));
			else
				strlcpy(cmd.parm.num, status + 1, sizeof(cmd.parm.num));
			break;
		case 8:
			/* Misc Errors on L1 and L2 */
			card->flags &= ~ISDNLOOP_FLAGS_B1ACTIVE;
			isdnloop_free_queue(card, 0);
			cmd.arg = 0;
			cmd.driver = card->myid;
			card->interface.statcallb(&cmd);
			cmd.command = ISDN_STAT_DHUP;
			cmd.arg = 0;
			cmd.driver = card->myid;
			card->interface.statcallb(&cmd);
			cmd.command = ISDN_STAT_BHUP;
			card->flags &= ~ISDNLOOP_FLAGS_B2ACTIVE;
			isdnloop_free_queue(card, 1);
			cmd.arg = 1;
			cmd.driver = card->myid;
			card->interface.statcallb(&cmd);
			cmd.command = ISDN_STAT_DHUP;
			cmd.arg = 1;
			cmd.driver = card->myid;
			break;
	}
	card->interface.statcallb(&cmd);
}