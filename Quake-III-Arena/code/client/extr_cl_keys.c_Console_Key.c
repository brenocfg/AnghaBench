#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  temp ;
struct TYPE_10__ {scalar_t__ state; } ;
struct TYPE_9__ {char* buffer; int /*<<< orphan*/  widthInChars; int /*<<< orphan*/  cursor; } ;
struct TYPE_8__ {scalar_t__ down; } ;

/* Variables and functions */
 scalar_t__ CA_ACTIVE ; 
 scalar_t__ CA_DISCONNECTED ; 
 size_t COMMAND_HISTORY ; 
 int /*<<< orphan*/  Cbuf_AddText (char*) ; 
 int /*<<< orphan*/  Com_Printf (char*,char*) ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  Con_Bottom () ; 
 int /*<<< orphan*/  Con_PageDown () ; 
 int /*<<< orphan*/  Con_PageUp () ; 
 int /*<<< orphan*/  Con_Top () ; 
 int /*<<< orphan*/  Field_Clear (TYPE_2__*) ; 
 int /*<<< orphan*/  Field_CompleteCommand (TYPE_2__*) ; 
 int /*<<< orphan*/  Field_KeyDownEvent (TYPE_2__*,int) ; 
 size_t K_CTRL ; 
 int K_DOWNARROW ; 
 int K_END ; 
 int K_ENTER ; 
 int K_HOME ; 
 int K_KP_DOWNARROW ; 
 int K_KP_ENTER ; 
 int K_KP_UPARROW ; 
 int K_MWHEELDOWN ; 
 int K_MWHEELUP ; 
 int K_PGDN ; 
 int K_PGUP ; 
 size_t K_SHIFT ; 
 int K_TAB ; 
 int K_UPARROW ; 
 int MAX_STRING_CHARS ; 
 int /*<<< orphan*/  Q_strncpyz (char*,char*,int) ; 
 int /*<<< orphan*/  SCR_UpdateScreen () ; 
 TYPE_4__ cls ; 
 TYPE_2__ g_consoleField ; 
 int /*<<< orphan*/  g_console_field_width ; 
 TYPE_2__* historyEditLines ; 
 size_t historyLine ; 
 TYPE_1__* keys ; 
 size_t nextHistoryLine ; 
 char tolower (int) ; 

void Console_Key (int key) {
	// ctrl-L clears screen
	if ( key == 'l' && keys[K_CTRL].down ) {
		Cbuf_AddText ("clear\n");
		return;
	}

	// enter finishes the line
	if ( key == K_ENTER || key == K_KP_ENTER ) {
		// if not in the game explicitly prepent a slash if needed
		if ( cls.state != CA_ACTIVE && g_consoleField.buffer[0] != '\\' 
			&& g_consoleField.buffer[0] != '/' ) {
			char	temp[MAX_STRING_CHARS];

			Q_strncpyz( temp, g_consoleField.buffer, sizeof( temp ) );
			Com_sprintf( g_consoleField.buffer, sizeof( g_consoleField.buffer ), "\\%s", temp );
			g_consoleField.cursor++;
		}

		Com_Printf ( "]%s\n", g_consoleField.buffer );

		// leading slash is an explicit command
		if ( g_consoleField.buffer[0] == '\\' || g_consoleField.buffer[0] == '/' ) {
			Cbuf_AddText( g_consoleField.buffer+1 );	// valid command
			Cbuf_AddText ("\n");
		} else {
			// other text will be chat messages
			if ( !g_consoleField.buffer[0] ) {
				return;	// empty lines just scroll the console without adding to history
			} else {
				Cbuf_AddText ("cmd say ");
				Cbuf_AddText( g_consoleField.buffer );
				Cbuf_AddText ("\n");
			}
		}

		// copy line to history buffer
		historyEditLines[nextHistoryLine % COMMAND_HISTORY] = g_consoleField;
		nextHistoryLine++;
		historyLine = nextHistoryLine;

		Field_Clear( &g_consoleField );

		g_consoleField.widthInChars = g_console_field_width;

		if ( cls.state == CA_DISCONNECTED ) {
			SCR_UpdateScreen ();	// force an update, because the command
		}							// may take some time
		return;
	}

	// command completion

	if (key == K_TAB) {
		Field_CompleteCommand(&g_consoleField);
		return;
	}

	// command history (ctrl-p ctrl-n for unix style)

	if ( (key == K_MWHEELUP && keys[K_SHIFT].down) || ( key == K_UPARROW ) || ( key == K_KP_UPARROW ) ||
		 ( ( tolower(key) == 'p' ) && keys[K_CTRL].down ) ) {
		if ( nextHistoryLine - historyLine < COMMAND_HISTORY 
			&& historyLine > 0 ) {
			historyLine--;
		}
		g_consoleField = historyEditLines[ historyLine % COMMAND_HISTORY ];
		return;
	}

	if ( (key == K_MWHEELDOWN && keys[K_SHIFT].down) || ( key == K_DOWNARROW ) || ( key == K_KP_DOWNARROW ) ||
		 ( ( tolower(key) == 'n' ) && keys[K_CTRL].down ) ) {
		if (historyLine == nextHistoryLine)
			return;
		historyLine++;
		g_consoleField = historyEditLines[ historyLine % COMMAND_HISTORY ];
		return;
	}

	// console scrolling
	if ( key == K_PGUP ) {
		Con_PageUp();
		return;
	}

	if ( key == K_PGDN) {
		Con_PageDown();
		return;
	}

	if ( key == K_MWHEELUP) {	//----(SA)	added some mousewheel functionality to the console
		Con_PageUp();
		if(keys[K_CTRL].down) {	// hold <ctrl> to accelerate scrolling
			Con_PageUp();
			Con_PageUp();
		}
		return;
	}

	if ( key == K_MWHEELDOWN) {	//----(SA)	added some mousewheel functionality to the console
		Con_PageDown();
		if(keys[K_CTRL].down) {	// hold <ctrl> to accelerate scrolling
			Con_PageDown();
			Con_PageDown();
		}
		return;
	}

	// ctrl-home = top of console
	if ( key == K_HOME && keys[K_CTRL].down ) {
		Con_Top();
		return;
	}

	// ctrl-end = bottom of console
	if ( key == K_END && keys[K_CTRL].down ) {
		Con_Bottom();
		return;
	}

	// pass to the normal editline routine
	Field_KeyDownEvent( &g_consoleField, key );
}