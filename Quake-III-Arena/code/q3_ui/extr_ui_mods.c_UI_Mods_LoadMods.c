#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dirlist ;
struct TYPE_3__ {char const** itemnames; int numitems; } ;
struct TYPE_4__ {char** descriptionList; char** fs_gameList; TYPE_1__ list; int /*<<< orphan*/  fs_game; int /*<<< orphan*/  fs_gamePtr; int /*<<< orphan*/  description; int /*<<< orphan*/  descriptionPtr; } ;

/* Variables and functions */
 int MAX_MODS ; 
 int /*<<< orphan*/  UI_Mods_ParseInfos (char*,char*) ; 
 TYPE_2__ s_mods ; 
 int strlen (char*) ; 
 int trap_FS_GetFileList (char*,char*,char*,int) ; 
 int /*<<< orphan*/  trap_Print (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va (char*,int) ; 

__attribute__((used)) static void UI_Mods_LoadMods( void ) {
	int		numdirs;
	char	dirlist[2048];
	char	*dirptr;
  char  *descptr;
	int		i;
	int		dirlen;

	s_mods.list.itemnames = (const char **)s_mods.descriptionList;
	s_mods.descriptionPtr = s_mods.description;
	s_mods.fs_gamePtr = s_mods.fs_game;

	// always start off with baseq3
	s_mods.list.numitems = 1;
	s_mods.list.itemnames[0] = s_mods.descriptionList[0] = "Quake III Arena";
	s_mods.fs_gameList[0] = "";

	numdirs = trap_FS_GetFileList( "$modlist", "", dirlist, sizeof(dirlist) );
	dirptr  = dirlist;
	for( i = 0; i < numdirs; i++ ) {
		dirlen = strlen( dirptr ) + 1;
    descptr = dirptr + dirlen;
  	UI_Mods_ParseInfos( dirptr, descptr);
    dirptr += dirlen + strlen(descptr) + 1;
	}

	trap_Print( va( "%i mods parsed\n", s_mods.list.numitems ) );
	if (s_mods.list.numitems > MAX_MODS) {
		s_mods.list.numitems = MAX_MODS;
	}
}