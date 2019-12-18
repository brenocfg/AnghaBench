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
typedef  int /*<<< orphan*/  demoExt ;
struct TYPE_2__ {int demoCount; int /*<<< orphan*/ * demoList; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,int) ; 
 int MAX_DEMOS ; 
 int /*<<< orphan*/  Q_stricmp (char*,char*) ; 
 int /*<<< orphan*/  Q_strupr (char*) ; 
 int /*<<< orphan*/  String_Alloc (char*) ; 
 int strlen (char*) ; 
 scalar_t__ trap_Cvar_VariableValue (char*) ; 
 int trap_FS_GetFileList (char*,char*,char*,int) ; 
 TYPE_1__ uiInfo ; 

__attribute__((used)) static void UI_LoadDemos() {
	char	demolist[4096];
	char demoExt[32];
	char	*demoname;
	int		i, len;

	Com_sprintf(demoExt, sizeof(demoExt), "dm_%d", (int)trap_Cvar_VariableValue("protocol"));

	uiInfo.demoCount = trap_FS_GetFileList( "demos", demoExt, demolist, 4096 );

	Com_sprintf(demoExt, sizeof(demoExt), ".dm_%d", (int)trap_Cvar_VariableValue("protocol"));

	if (uiInfo.demoCount) {
		if (uiInfo.demoCount > MAX_DEMOS) {
			uiInfo.demoCount = MAX_DEMOS;
		}
		demoname = demolist;
		for ( i = 0; i < uiInfo.demoCount; i++ ) {
			len = strlen( demoname );
			if (!Q_stricmp(demoname +  len - strlen(demoExt), demoExt)) {
				demoname[len-strlen(demoExt)] = '\0';
			}
			Q_strupr(demoname);
			uiInfo.demoList[i] = String_Alloc(demoname);
			demoname += len + 1;
		}
	}

}