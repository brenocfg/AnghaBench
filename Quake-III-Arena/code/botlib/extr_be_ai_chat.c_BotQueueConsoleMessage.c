#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int handle; int type; struct TYPE_6__* prev; struct TYPE_6__* next; int /*<<< orphan*/  message; int /*<<< orphan*/  time; } ;
typedef  TYPE_1__ bot_consolemessage_t ;
struct TYPE_7__ {int handle; int /*<<< orphan*/  numconsolemessages; TYPE_1__* firstmessage; TYPE_1__* lastmessage; } ;
typedef  TYPE_2__ bot_chatstate_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_Time () ; 
 TYPE_1__* AllocConsoleMessage () ; 
 TYPE_2__* BotChatStateFromHandle (int) ; 
 int /*<<< orphan*/  MAX_MESSAGE_SIZE ; 
 int /*<<< orphan*/  PRT_ERROR ; 
 TYPE_3__ botimport ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

void BotQueueConsoleMessage(int chatstate, int type, char *message)
{
	bot_consolemessage_t *m;
	bot_chatstate_t *cs;

	cs = BotChatStateFromHandle(chatstate);
	if (!cs) return;

	m = AllocConsoleMessage();
	if (!m)
	{
		botimport.Print(PRT_ERROR, "empty console message heap\n");
		return;
	} //end if
	cs->handle++;
	if (cs->handle <= 0 || cs->handle > 8192) cs->handle = 1;
	m->handle = cs->handle;
	m->time = AAS_Time();
	m->type = type;
	strncpy(m->message, message, MAX_MESSAGE_SIZE);
	m->next = NULL;
	if (cs->lastmessage)
	{
		cs->lastmessage->next = m;
		m->prev = cs->lastmessage;
		cs->lastmessage = m;
	} //end if
	else
	{
		cs->lastmessage = m;
		cs->firstmessage = m;
		m->prev = NULL;
	} //end if
	cs->numconsolemessages++;
}