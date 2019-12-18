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
 int /*<<< orphan*/  CURSES_CENTRAL ; 
 int /*<<< orphan*/  CURSES_LEFT ; 
 int /*<<< orphan*/  CURSES_RIGHT ; 
 int /*<<< orphan*/  CURSES_WIDE_1 ; 
 int /*<<< orphan*/  CURSES_WIDE_2 ; 
 int FALSE ; 
 int /*<<< orphan*/  Log_print (char*) ; 
 int /*<<< orphan*/  Sound_Initialise (int*,char**) ; 
 int TRUE ; 
 int /*<<< orphan*/  cbreak () ; 
 int /*<<< orphan*/  curs_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curses_mode ; 
 int /*<<< orphan*/  initscr () ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nodelay (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  noecho () ; 
 int /*<<< orphan*/  stdscr ; 
 scalar_t__ strcmp (char*,char*) ; 

int PLATFORM_Initialise(int *argc, char *argv[])
{
	int i;
	int j;

	for (i = j = 1; i < *argc; i++) {
		if (strcmp(argv[i], "-left") == 0)
			curses_mode = CURSES_LEFT;
		else if (strcmp(argv[i], "-central") == 0)
			curses_mode = CURSES_CENTRAL;
		else if (strcmp(argv[i], "-right") == 0)
			curses_mode = CURSES_RIGHT;
		else if (strcmp(argv[i], "-wide1") == 0)
			curses_mode = CURSES_WIDE_1;
		else if (strcmp(argv[i], "-wide2") == 0)
			curses_mode = CURSES_WIDE_2;
		else {
			if (strcmp(argv[i], "-help") == 0) {
				Log_print("\t-central         Center emulated screen\n"
				       "\t-left            Align left\n"
				       "\t-right           Align right (on 80 columns)\n"
				       "\t-wide1           Use 80 columns\n"
				       "\t-wide2           Use 80 columns, display twice"
				      );
			}
			argv[j++] = argv[i];
		}
	}

	*argc = j;

	initscr();
	noecho();
	cbreak();					/* Don't wait for carriage return */
	keypad(stdscr, TRUE);
	curs_set(0);				/* Disable Cursor */
	nodelay(stdscr, 1);			/* Don't block for keypress */

#ifdef SOUND
	if (!Sound_Initialise(argc, argv))
		return FALSE;
#endif

	return TRUE;
}