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
typedef  int /*<<< orphan*/  name ;
struct TYPE_2__ {char** placeNames; scalar_t__* clientNums; } ;

/* Variables and functions */
 scalar_t__ CS_PLAYERS ; 
 char* Info_ValueForKey (char*,char*) ; 
 int MAX_INFO_STRING ; 
 int /*<<< orphan*/  Q_CleanStr (char*) ; 
 int /*<<< orphan*/  Q_strncpyz (char*,char*,int) ; 
 int UI_ProportionalStringWidth (char*) ; 
 TYPE_1__ postgameMenuInfo ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  trap_GetConfigString (scalar_t__,char*,int) ; 

__attribute__((used)) static void Prepname( int index ) {
	int		len;
	char	name[64];
	char	info[MAX_INFO_STRING];

	trap_GetConfigString( CS_PLAYERS + postgameMenuInfo.clientNums[index], info, MAX_INFO_STRING );
	Q_strncpyz( name, Info_ValueForKey( info, "n" ), sizeof(name) );
	Q_CleanStr( name );
	len = strlen( name );

	while( len && UI_ProportionalStringWidth( name ) > 256 ) {
		len--;
		name[len] = 0;
	}

	Q_strncpyz( postgameMenuInfo.placeNames[index], name, sizeof(postgameMenuInfo.placeNames[index]) );
}