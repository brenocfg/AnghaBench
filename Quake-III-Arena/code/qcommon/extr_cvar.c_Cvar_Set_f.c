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
 int Cmd_Argc () ; 
 char* Cmd_Argv (int) ; 
 int /*<<< orphan*/  Com_Printf (char*) ; 
 int /*<<< orphan*/  Cvar_Set2 (char*,char*,int /*<<< orphan*/ ) ; 
 int MAX_STRING_TOKENS ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 

void Cvar_Set_f( void ) {
	int		i, c, l, len;
	char	combined[MAX_STRING_TOKENS];

	c = Cmd_Argc();
	if ( c < 3 ) {
		Com_Printf ("usage: set <variable> <value>\n");
		return;
	}

	combined[0] = 0;
	l = 0;
	for ( i = 2 ; i < c ; i++ ) {
		len = strlen ( Cmd_Argv( i ) + 1 );
		if ( l + len >= MAX_STRING_TOKENS - 2 ) {
			break;
		}
		strcat( combined, Cmd_Argv( i ) );
		if ( i != c-1 ) {
			strcat( combined, " " );
		}
		l += len;
	}
	Cvar_Set2 (Cmd_Argv(1), combined, qfalse);
}