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
 int /*<<< orphan*/  Util_chomp (char*) ; 
 int /*<<< orphan*/  add_history (char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fgets (char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* readline (char const*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 

__attribute__((used)) static void safe_gets(char *buffer, size_t size, char const *prompt)
{
#ifdef HAVE_FFLUSH
	fflush(stdout);
#endif

#ifdef MONITOR_READLINE
	{
		char *got = readline(prompt);
		if (got) {
			strncpy(buffer, got, size);
			if (*got)
				add_history(got);
			free(got); /* Need to free buffer allocated by readline() */
		}
	}
#else
	fputs(prompt, stdout);
	fgets(buffer, size, stdin);
#endif
	Util_chomp(buffer);
}