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
struct TYPE_2__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,int) ;} ;

/* Variables and functions */
 int BLERR_NOERROR ; 
 int /*<<< orphan*/  BotLoadMatchTemplates (char*) ; 
 int /*<<< orphan*/  BotLoadRandomStrings (char*) ; 
 int /*<<< orphan*/  BotLoadReplyChat (char*) ; 
 int /*<<< orphan*/  BotLoadSynonyms (char*) ; 
 int /*<<< orphan*/  InitConsoleMessageHeap () ; 
 char* LibVarString (char*,char*) ; 
 int /*<<< orphan*/  LibVarValue (char*,char*) ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 int Sys_MilliSeconds () ; 
 TYPE_1__ botimport ; 
 int /*<<< orphan*/  matchtemplates ; 
 int /*<<< orphan*/  randomstrings ; 
 int /*<<< orphan*/  replychats ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  synonyms ; 

int BotSetupChatAI(void)
{
	char *file;

#ifdef DEBUG
	int starttime = Sys_MilliSeconds();
#endif //DEBUG

	file = LibVarString("synfile", "syn.c");
	synonyms = BotLoadSynonyms(file);
	file = LibVarString("rndfile", "rnd.c");
	randomstrings = BotLoadRandomStrings(file);
	file = LibVarString("matchfile", "match.c");
	matchtemplates = BotLoadMatchTemplates(file);
	//
	if (!LibVarValue("nochat", "0"))
	{
		file = LibVarString("rchatfile", "rchat.c");
		replychats = BotLoadReplyChat(file);
	} //end if

	InitConsoleMessageHeap();

#ifdef DEBUG
	botimport.Print(PRT_MESSAGE, "setup chat AI %d msec\n", Sys_MilliSeconds() - starttime);
#endif //DEBUG
	return BLERR_NOERROR;
}