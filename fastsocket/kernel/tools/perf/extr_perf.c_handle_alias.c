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
struct strbuf {char* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_MAX ; 
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 char* alias_lookup (char const*) ; 
 int /*<<< orphan*/  die (char*,char const*,...) ; 
 int errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int handle_options (char const***,int*,int*) ; 
 int /*<<< orphan*/  memcpy (char const**,char const**,int) ; 
 int /*<<< orphan*/  memmove (char const**,char const**,int) ; 
 char** realloc (char const**,int) ; 
 int split_cmdline (char*,char const***) ; 
 int /*<<< orphan*/  sq_quote_argv (struct strbuf*,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_init (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 int system (char*) ; 

__attribute__((used)) static int handle_alias(int *argcp, const char ***argv)
{
	int envchanged = 0, ret = 0, saved_errno = errno;
	int count, option_count;
	const char **new_argv;
	const char *alias_command;
	char *alias_string;

	alias_command = (*argv)[0];
	alias_string = alias_lookup(alias_command);
	if (alias_string) {
		if (alias_string[0] == '!') {
			if (*argcp > 1) {
				struct strbuf buf;

				strbuf_init(&buf, PATH_MAX);
				strbuf_addstr(&buf, alias_string);
				sq_quote_argv(&buf, (*argv) + 1, PATH_MAX);
				free(alias_string);
				alias_string = buf.buf;
			}
			ret = system(alias_string + 1);
			if (ret >= 0 && WIFEXITED(ret) &&
			    WEXITSTATUS(ret) != 127)
				exit(WEXITSTATUS(ret));
			die("Failed to run '%s' when expanding alias '%s'",
			    alias_string + 1, alias_command);
		}
		count = split_cmdline(alias_string, &new_argv);
		if (count < 0)
			die("Bad alias.%s string", alias_command);
		option_count = handle_options(&new_argv, &count, &envchanged);
		if (envchanged)
			die("alias '%s' changes environment variables\n"
				 "You can use '!perf' in the alias to do this.",
				 alias_command);
		memmove(new_argv - option_count, new_argv,
				count * sizeof(char *));
		new_argv -= option_count;

		if (count < 1)
			die("empty alias for %s", alias_command);

		if (!strcmp(alias_command, new_argv[0]))
			die("recursive alias: %s", alias_command);

		new_argv = realloc(new_argv, sizeof(char *) *
				    (count + *argcp + 1));
		/* insert after command name */
		memcpy(new_argv + count, *argv + 1, sizeof(char *) * *argcp);
		new_argv[count + *argcp] = NULL;

		*argv = new_argv;
		*argcp += count - 1;

		ret = 1;
	}

	errno = saved_errno;

	return ret;
}