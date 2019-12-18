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
struct console_cmdline {int index; char* options; char* brl_options; scalar_t__* name; } ;

/* Variables and functions */
 int E2BIG ; 
 int MAX_CMDLINECONSOLES ; 
 struct console_cmdline* console_cmdline ; 
 int selected_console ; 
 scalar_t__ strcmp (scalar_t__*,char*) ; 
 int /*<<< orphan*/  strlcpy (scalar_t__*,char*,int) ; 

__attribute__((used)) static int __add_preferred_console(char *name, int idx, char *options,
				   char *brl_options)
{
	struct console_cmdline *c;
	int i;

	/*
	 *	See if this tty is not yet registered, and
	 *	if we have a slot free.
	 */
	for (i = 0; i < MAX_CMDLINECONSOLES && console_cmdline[i].name[0]; i++)
		if (strcmp(console_cmdline[i].name, name) == 0 &&
			  console_cmdline[i].index == idx) {
				if (!brl_options)
					selected_console = i;
				return 0;
		}
	if (i == MAX_CMDLINECONSOLES)
		return -E2BIG;
	if (!brl_options)
		selected_console = i;
	c = &console_cmdline[i];
	strlcpy(c->name, name, sizeof(c->name));
	c->options = options;
#ifdef CONFIG_A11Y_BRAILLE_CONSOLE
	c->brl_options = brl_options;
#endif
	c->index = idx;
	return 0;
}