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
 int /*<<< orphan*/  Box (int,int,int,int,int,int) ; 
 int FALSE ; 
 int FILENAME_MAX ; 
 int /*<<< orphan*/  FileSelector (char*,int,char**,int) ; 
 int GetKeyPress () ; 
 int /*<<< orphan*/  Plot (int,int,char,int,int) ; 
 int /*<<< orphan*/  Print (int,int,char const*,int,int,int) ; 
 int TRUE ; 
 int /*<<< orphan*/  Util_catpath (char*,char*,char*) ; 
 int /*<<< orphan*/  Util_splitpath (char*,char*,char*) ; 
 int /*<<< orphan*/  Util_stpcpy (char*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int EditString(int fg, int bg, const char *title,
                      char *string, int size, int x, int y, int width,
                      char pDirectories[][FILENAME_MAX], int nDirectories)
{
	int caret = strlen(string);
	int offset = 0;
	for (;;) {
		int i;
		char *p;
		int ascii;
		Box(fg, bg, x, y, x + 1 + width, y + 2);
		Print(bg, fg, title, x + 1, y, width);
		if (caret - offset >= width)
			offset = caret - width + 1;
		else if (caret < offset)
			offset = caret;
		p = string + offset;
		for (i = 0; i < width; i++)
			if (offset + i == caret)
				Plot(bg, fg, *p != '\0' ? *p++ : ' ', x + 1 + i, y + 1);
			else
				Plot(fg, bg, *p != '\0' ? *p++ : ' ', x + 1 + i, y + 1);
		ascii = GetKeyPress();
		switch (ascii) {
		case 0x1e:				/* Cursor Left */
			if (caret > 0)
				caret--;
			break;
		case 0x1f:				/* Cursor Right */
			if (string[caret] != '\0')
				caret++;
			break;
		case 0x7e:				/* Backspace */
			if (caret > 0) {
				caret--;
				p = string + caret;
				do
					p[0] = p[1];
				while (*p++ != '\0');
			}
			break;
		case 0xfe:				/* Delete */
			if (string[caret] != '\0') {
				p = string + caret;
				do
					p[0] = p[1];
				while (*p++ != '\0');
			}
			break;
		case 0x7d:				/* Clear screen */
		case 0x9c:				/* Delete line */
			caret = 0;
			string[0] = '\0';
			break;
		case 0x9b:				/* Return */
			if (nDirectories >= 0) {
				/* check filename */
				char lastchar;
				if (string[0] == '\0')
					return FALSE;
				lastchar = string[strlen(string) - 1];
				return lastchar != '/' && lastchar != '\\';
			}
			return TRUE;
		case 0x1b:				/* Esc */
			return FALSE;
#ifdef DO_DIR
		case 0x7f:				/* Tab = select directory */
			if (nDirectories >= 0) {
				char temp_filename[FILENAME_MAX + 1];
				char temp_path[FILENAME_MAX];
				char temp_file[FILENAME_MAX];
				char *s;
				/* FIXME: now we append '*' and then discard it
				   just to workaround Util_splitpath() not recognizing
				   Util_DIR_SEP_CHAR when it's the last character */
				strcpy(Util_stpcpy(temp_filename, string), "*");
				Util_splitpath(temp_filename, temp_path, temp_file);
				s = temp_file + strlen(temp_file) - 1;
				if (*s == '*') { /* XXX: should be always... */
					*s = '\0';
					if (FileSelector(temp_path, TRUE, pDirectories, nDirectories)) {
						Util_catpath(string, temp_path, temp_file);
						caret = strlen(string);
						offset = 0;
					}
				}
			}
			break;
#endif
		default:
			/* Insert character */
			i = strlen(string);
			if (i + 1 < size && ascii >= ' ' && ascii < 0x7f) {
				do
					string[i + 1] = string[i];
				while (--i >= caret);
				string[caret++] = (char) ascii;
			}
			break;
		}
	}
}