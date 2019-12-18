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
 int /*<<< orphan*/  BasicUIMessage (char*,int) ; 
 int /*<<< orphan*/  Box (int,int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  ClearScreen () ; 
 int FALSE ; 
 int FILENAME_MAX ; 
 int /*<<< orphan*/  FilenamesFree () ; 
 int /*<<< orphan*/  GetCurrentDir (char*) ; 
 int /*<<< orphan*/  GetDirectory (char*) ; 
 int NCOLUMNS ; 
 int /*<<< orphan*/  NROWS ; 
 int /*<<< orphan*/  PLATFORM_DisplayScreen () ; 
 int Select (int,int,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int,int,char*,int*) ; 
 int TRUE ; 
 int /*<<< orphan*/  TitleScreen (char*) ; 
 int UI_USER_DELETE ; 
 int UI_USER_TOGGLE ; 
 int /*<<< orphan*/  Util_catpath (char*,char*,char const*) ; 
 scalar_t__ Util_direxists (char*) ; 
 int /*<<< orphan*/  Util_splitpath (char*,char*,char*) ; 
 int /*<<< orphan*/  _fixpath (char*,char*) ; 
 char const** filenames ; 
 int n_filenames ; 
 int /*<<< orphan*/  strcatchr (char*,char) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static int FileSelector(char *path, int select_dir, char pDirectories[][FILENAME_MAX], int nDirectories)
{
	char current_dir[FILENAME_MAX];
	char highlighted_file[FILENAME_MAX + 2]; /* +2 for square brackets */
	highlighted_file[0] = '\0';
	if (path[0] == '\0' && nDirectories > 0)
		strcpy(current_dir, pDirectories[0]);
	else if (select_dir)
		strcpy(current_dir, path);
	else
		Util_splitpath(path, current_dir, highlighted_file);
#ifdef __DJGPP__
	{
		char help_dir[FILENAME_MAX];
		_fixpath(current_dir, help_dir);
		strcpy(current_dir, help_dir);
	}
#elif defined(HAVE_GETCWD)
	if (current_dir[0] == '\0' || (current_dir[0] == '.' && current_dir[1] == '\0'))
#else
	if (current_dir[0] == '\0')
#endif
		GetCurrentDir(current_dir);
	for (;;) {
		int index = 0;
		int i;

#define NROWS 20
#define NCOLUMNS 2
#define MAX_FILES (NROWS * NCOLUMNS)

		/* The WinCE version may spend several seconds when there are many
		   files in the directory. */
		/* The extra spaces are needed to clear the previous window title. */
		TitleScreen("            Please wait...            ");
		PLATFORM_DisplayScreen();

		for (;;) {
			GetDirectory(current_dir);

			if (n_filenames > 0)
				break;

			/* Can't read directory - maybe it doesn't exist?
			   Split the last part from the path and try again. */
			FilenamesFree();
			{
				char temp[FILENAME_MAX];
				strcpy(temp, current_dir);
				Util_splitpath(temp, current_dir, NULL);
			}
			if (current_dir[0] == '\0') {
				/* Path couldn't be split further.
				   Try the working directory as a last resort. */
				GetCurrentDir(current_dir);
				GetDirectory(current_dir);
				if (n_filenames >= 0)
					break;

				FilenamesFree();
				BasicUIMessage("No files inside directory", 1);
				return FALSE;
			}
		}

		if (highlighted_file[0] != '\0') {
			for (i = 0; i < n_filenames; i++) {
				if (strcmp(filenames[i], highlighted_file) == 0) {
					index = i;
					break;
				}
			}
		}

		for (;;) {
			int seltype;
			const char *selected_filename;

			ClearScreen();
			TitleScreen(current_dir);
			Box(0x9a, 0x94, 0, 1, 39, 23);

			index = Select(index, n_filenames, filenames, NULL, NULL, NULL, NULL,
			               NROWS, NCOLUMNS, 1, 2, 37 / NCOLUMNS, FALSE,
			               select_dir ? "Space: select current directory" : NULL,
			               &seltype);

			if (index == -2) {
				/* Tab = next favourite directory */
				if (nDirectories > 0) {
					/* default: pDirectories[0] */
					int current_index = nDirectories - 1;
					/* are we in one of pDirectories? */
					for (i = 0; i < nDirectories; i++)
						if (strcmp(pDirectories[i], current_dir) == 0) {
							current_index = i;
							break;
						}
					i = current_index;
					do {
						if (++i >= nDirectories)
							i = 0;
						if (Util_direxists(pDirectories[i])) {
							strcpy(current_dir, pDirectories[i]);
							break;
						}
					} while (i != current_index);
				}
				highlighted_file[0] = '\0';
				break;
			}
			if (index < 0) {
				/* Esc = cancel */
				FilenamesFree();
				return FALSE;
			}
			if (seltype == UI_USER_DELETE) {
				/* Backspace = parent directory */
				char new_dir[FILENAME_MAX];
				Util_splitpath(current_dir, new_dir, highlighted_file + 1);
				if (Util_direxists(new_dir)) {
					strcpy(current_dir, new_dir);
					highlighted_file[0] = '[';
					strcatchr(highlighted_file, ']');
					break;
				}
				BasicUIMessage("Cannot enter parent directory", 1);
				continue;
			}
			if (seltype == UI_USER_TOGGLE && select_dir) {
				/* Space = select current directory */
				strcpy(path, current_dir);
				FilenamesFree();
				return TRUE;
			}
			selected_filename = filenames[index];
			if (selected_filename[0] == '[') {
				/* Change directory */
				char new_dir[FILENAME_MAX];

				highlighted_file[0] = '\0';
				if (strcmp(selected_filename, "[..]") == 0) {
					/* go up */
					Util_splitpath(current_dir, new_dir, highlighted_file + 1);
					highlighted_file[0] = '[';
					strcatchr(highlighted_file, ']');
				}
#ifdef PS2
				else if (strcmp(selected_filename, "[mc0:]") == 0) {
					strcpy(new_dir, "mc0:/");
				}
#endif
#ifdef DOS_DRIVES
				else if (selected_filename[2] == ':' && selected_filename[3] == ']') {
					/* disk selected */
					new_dir[0] = selected_filename[1];
					new_dir[1] = ':';
					new_dir[2] = '\\';
					new_dir[3] = '\0';
				}
#endif
				else {
					/* directory selected */
					char *pbracket = strrchr(selected_filename, ']');
					if (pbracket == NULL)
						continue; /* XXX: regular file? */
					*pbracket = '\0';	/*cut ']' */
					Util_catpath(new_dir, current_dir, selected_filename + 1);
				}
				/* check if new directory is valid */
				if (Util_direxists(new_dir)) {
					strcpy(current_dir, new_dir);
					break;
				}
				BasicUIMessage("Cannot enter selected directory", 1);
				continue;
			}
			if (!select_dir) {
				/* normal filename selected */
				Util_catpath(path, current_dir, selected_filename);
				FilenamesFree();
				return TRUE;
			}
		}

		FilenamesFree();
	}
}