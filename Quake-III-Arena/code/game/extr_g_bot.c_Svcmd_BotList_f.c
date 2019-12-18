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
 char* Info_ValueForKey (int /*<<< orphan*/ ,char*) ; 
 int MAX_TOKEN_CHARS ; 
 int /*<<< orphan*/ * g_botInfos ; 
 int g_numBots ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  trap_Printf (char*) ; 
 char* va (char*,char*,char*,char*,char*) ; 

void Svcmd_BotList_f( void ) {
	int i;
	char name[MAX_TOKEN_CHARS];
	char funname[MAX_TOKEN_CHARS];
	char model[MAX_TOKEN_CHARS];
	char aifile[MAX_TOKEN_CHARS];

	trap_Printf("^1name             model            aifile              funname\n");
	for (i = 0; i < g_numBots; i++) {
		strcpy(name, Info_ValueForKey( g_botInfos[i], "name" ));
		if ( !*name ) {
			strcpy(name, "UnnamedPlayer");
		}
		strcpy(funname, Info_ValueForKey( g_botInfos[i], "funname" ));
		if ( !*funname ) {
			strcpy(funname, "");
		}
		strcpy(model, Info_ValueForKey( g_botInfos[i], "model" ));
		if ( !*model ) {
			strcpy(model, "visor/default");
		}
		strcpy(aifile, Info_ValueForKey( g_botInfos[i], "aifile"));
		if (!*aifile ) {
			strcpy(aifile, "bots/default_c.c");
		}
		trap_Printf(va("%-16s %-16s %-20s %-20s\n", name, model, aifile, funname));
	}
}