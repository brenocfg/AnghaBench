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
typedef  int /*<<< orphan*/  bot_consolemessage_t ;
typedef  int /*<<< orphan*/  bot_chatstate_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BotFreeChatFile (int) ; 
 int BotNextConsoleMessage (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BotRemoveConsoleMessage (int,int) ; 
 int /*<<< orphan*/  FreeMemory (int /*<<< orphan*/ *) ; 
 scalar_t__ LibVarGetValue (char*) ; 
 int MAX_CLIENTS ; 
 int /*<<< orphan*/  PRT_FATAL ; 
 int /*<<< orphan*/ ** botchatstates ; 
 TYPE_1__ botimport ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*,int) ; 

void BotFreeChatState(int handle)
{
	bot_chatstate_t *cs;
	bot_consolemessage_t m;
	int h;

	if (handle <= 0 || handle > MAX_CLIENTS)
	{
		botimport.Print(PRT_FATAL, "chat state handle %d out of range\n", handle);
		return;
	} //end if
	if (!botchatstates[handle])
	{
		botimport.Print(PRT_FATAL, "invalid chat state %d\n", handle);
		return;
	} //end if
	cs = botchatstates[handle];
	if (LibVarGetValue("bot_reloadcharacters"))
	{
		BotFreeChatFile(handle);
	} //end if
	//free all the console messages left in the chat state
	for (h = BotNextConsoleMessage(handle, &m); h; h = BotNextConsoleMessage(handle, &m))
	{
		//remove the console message
		BotRemoveConsoleMessage(handle, h);
	} //end for
	FreeMemory(botchatstates[handle]);
	botchatstates[handle] = NULL;
}