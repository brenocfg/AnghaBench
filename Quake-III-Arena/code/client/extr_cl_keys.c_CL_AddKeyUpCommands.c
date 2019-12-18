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
typedef  scalar_t__ qboolean ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  Cbuf_AddText (char*) ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 
 int /*<<< orphan*/  time ; 

void CL_AddKeyUpCommands( int key, char *kb ) {
	int i;
	char button[1024], *buttonPtr;
	char	cmd[1024];
	qboolean keyevent;

	if ( !kb ) {
		return;
	}
	keyevent = qfalse;
	buttonPtr = button;
	for ( i = 0; ; i++ ) {
		if ( kb[i] == ';' || !kb[i] ) {
			*buttonPtr = '\0';
			if ( button[0] == '+') {
				// button commands add keynum and time as parms so that multiple
				// sources can be discriminated and subframe corrected
				Com_sprintf (cmd, sizeof(cmd), "-%s %i %i\n", button+1, key, time);
				Cbuf_AddText (cmd);
				keyevent = qtrue;
			} else {
				if (keyevent) {
					// down-only command
					Cbuf_AddText (button);
					Cbuf_AddText ("\n");
				}
			}
			buttonPtr = button;
			while ( (kb[i] <= ' ' || kb[i] == ';') && kb[i] != 0 ) {
				i++;
			}
		}
		*buttonPtr++ = kb[i];
		if ( !kb[i] ) {
			break;
		}
	}
}