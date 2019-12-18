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
struct TYPE_2__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*) ;} ;

/* Variables and functions */
 int BLERR_CANNOTLOADITEMCONFIG ; 
 int BLERR_NOERROR ; 
 int /*<<< orphan*/  LibVar (char*,char*) ; 
 char* LibVarString (char*,char*) ; 
 int /*<<< orphan*/  LibVarValue (char*,char*) ; 
 int /*<<< orphan*/  LoadItemConfig (char*) ; 
 int /*<<< orphan*/  PRT_FATAL ; 
 TYPE_1__ botimport ; 
 int /*<<< orphan*/  droppedweight ; 
 int /*<<< orphan*/  g_gametype ; 
 int /*<<< orphan*/  itemconfig ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

int BotSetupGoalAI(void)
{
	char *filename;

	//check if teamplay is on
	g_gametype = LibVarValue("g_gametype", "0");
	//item configuration file
	filename = LibVarString("itemconfig", "items.c");
	//load the item configuration
	itemconfig = LoadItemConfig(filename);
	if (!itemconfig)
	{
		botimport.Print(PRT_FATAL, "couldn't load item config\n");
		return BLERR_CANNOTLOADITEMCONFIG;
	} //end if
	//
	droppedweight = LibVar("droppedweight", "1000");
	//everything went ok
	return BLERR_NOERROR;
}