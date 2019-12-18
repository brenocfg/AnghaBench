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
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* AUTOFORMAT ; 
 char* CASE ; 
 char* EIGHTBIT ; 
 char* EMACS_string ; 
 char* EXPAND ; 
 int /*<<< orphan*/  Echo ; 
 int /*<<< orphan*/  FALSE ; 
 char* HIGHLIGHT ; 
 char* INFO ; 
 char* MARGINS ; 
 char* NOAUTOFORMAT ; 
 char* NOCASE ; 
 char* NOEIGHTBIT ; 
 char* NOEMACS_string ; 
 char* NOEXPAND ; 
 char* NOHIGHLIGHT ; 
 char* NOINFO ; 
 char* NOMARGINS ; 
 char* PRINTCOMMAND ; 
 char* RIGHTMARGIN ; 
 scalar_t__ auto_format ; 
 scalar_t__ case_sen ; 
 char* chinese_cmd ; 
 int /*<<< orphan*/  com_win ; 
 scalar_t__ compare (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conf_dump_err_msg ; 
 int /*<<< orphan*/  conf_dump_success_msg ; 
 int /*<<< orphan*/  conf_not_saved_msg ; 
 int /*<<< orphan*/  config_dump_menu ; 
 scalar_t__ ee_chinese ; 
 scalar_t__ eightbit ; 
 scalar_t__ emacs_keys_mode ; 
 scalar_t__ expand_tabs ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ info_window ; 
 int /*<<< orphan*/  init_strings ; 
 int /*<<< orphan*/  link (char*,char*) ; 
 int menu_op (int /*<<< orphan*/ ) ; 
 char* nochinese_cmd ; 
 scalar_t__ nohighlight ; 
 scalar_t__ observ_margins ; 
 char* print_command ; 
 char* resolve_name (char*) ; 
 scalar_t__ restrict_mode () ; 
 int right_margin ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int stat (char*,struct stat*) ; 
 int strlen (char*) ; 
 int unique_test (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  werase (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wprintw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ ) ; 

void 
dump_ee_conf()	
{
	FILE *init_file;
	FILE *old_init_file = NULL;
	char *file_name = ".init.ee";
	char *home_dir =  "~/.init.ee";
	char buffer[512];
	struct stat buf;
	char *string;
	int length;
	int option = 0;

	if (restrict_mode())
	{
		return;
	}

	option = menu_op(config_dump_menu);

	werase(com_win);
	wmove(com_win, 0, 0);

	if (option == 0)
	{
		wprintw(com_win, conf_not_saved_msg);
		wrefresh(com_win);
		return;
	}
	else if (option == 2)
		file_name = resolve_name(home_dir);

	/*
	 |	If a .init.ee file exists, move it to .init.ee.old.
	 */

	if (stat(file_name, &buf) != -1)
	{
		sprintf(buffer, "%s.old", file_name);
		unlink(buffer);
		link(file_name, buffer);
		unlink(file_name);
		old_init_file = fopen(buffer, "r");
	}

	init_file = fopen(file_name, "w");
	if (init_file == NULL)
	{
		wprintw(com_win, conf_dump_err_msg);
		wrefresh(com_win);
		return;
	}

	if (old_init_file != NULL)
	{
		/*
		 |	Copy non-configuration info into new .init.ee file.
		 */
		while ((string = fgets(buffer, 512, old_init_file)) != NULL)
		{
			length = strlen(string);
			string[length - 1] = '\0';

			if (unique_test(string, init_strings) == 1)
			{
				if (compare(string, Echo, FALSE))
				{
					fprintf(init_file, "%s\n", string);
				}
			}
			else
				fprintf(init_file, "%s\n", string);
		}

		fclose(old_init_file);
	}

	fprintf(init_file, "%s\n", case_sen ? CASE : NOCASE);
	fprintf(init_file, "%s\n", expand_tabs ? EXPAND : NOEXPAND);
	fprintf(init_file, "%s\n", info_window ? INFO : NOINFO );
	fprintf(init_file, "%s\n", observ_margins ? MARGINS : NOMARGINS );
	fprintf(init_file, "%s\n", auto_format ? AUTOFORMAT : NOAUTOFORMAT );
	fprintf(init_file, "%s %s\n", PRINTCOMMAND, print_command);
	fprintf(init_file, "%s %d\n", RIGHTMARGIN, right_margin);
	fprintf(init_file, "%s\n", nohighlight ? NOHIGHLIGHT : HIGHLIGHT );
	fprintf(init_file, "%s\n", eightbit ? EIGHTBIT : NOEIGHTBIT );
	fprintf(init_file, "%s\n", emacs_keys_mode ? EMACS_string : NOEMACS_string );
	fprintf(init_file, "%s\n", ee_chinese ? chinese_cmd : nochinese_cmd );

	fclose(init_file);

	wprintw(com_win, conf_dump_success_msg, file_name);
	wrefresh(com_win);

	if ((option == 2) && (file_name != home_dir))
	{
		free(file_name);
	}
}