#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int handle; int /*<<< orphan*/ * prev; int /*<<< orphan*/  next; } ;
typedef  TYPE_1__ bot_consolemessage_t ;
struct TYPE_7__ {scalar_t__ firstmessage; } ;
typedef  TYPE_2__ bot_chatstate_t ;

/* Variables and functions */
 TYPE_2__* BotChatStateFromHandle (int) ; 
 int /*<<< orphan*/  Com_Memcpy (TYPE_1__*,scalar_t__,int) ; 

int BotNextConsoleMessage(int chatstate, bot_consolemessage_t *cm)
{
	bot_chatstate_t *cs;

	cs = BotChatStateFromHandle(chatstate);
	if (!cs) return 0;
	if (cs->firstmessage)
	{
		Com_Memcpy(cm, cs->firstmessage, sizeof(bot_consolemessage_t));
		cm->next = cm->prev = NULL;
		return cm->handle;
	} //end if
	return 0;
}