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
struct arglist {int count; char** args; } ;

/* Variables and functions */
 int /*<<< orphan*/  errout ; 
 char* expandstr (char const*) ; 
 int /*<<< orphan*/  flushout (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out2 ; 
 int /*<<< orphan*/  out2c (char) ; 
 int /*<<< orphan*/  out2qstr (char const*) ; 
 int /*<<< orphan*/  out2str (char const*) ; 
 int /*<<< orphan*/  outbin (char const*,char const*,int /*<<< orphan*/ ) ; 
 char const* ps4val () ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static void
xtracecommand(struct arglist *varlist, int argc, char **argv)
{
	char sep = 0;
	const char *text, *p, *ps4;
	int i;

	ps4 = expandstr(ps4val());
	out2str(ps4 != NULL ? ps4 : ps4val());
	for (i = 0; i < varlist->count; i++) {
		text = varlist->args[i];
		if (sep != 0)
			out2c(' ');
		p = strchr(text, '=');
		if (p != NULL) {
			p++;
			outbin(text, p - text, out2);
			out2qstr(p);
		} else
			out2qstr(text);
		sep = ' ';
	}
	for (i = 0; i < argc; i++) {
		text = argv[i];
		if (sep != 0)
			out2c(' ');
		out2qstr(text);
		sep = ' ';
	}
	out2c('\n');
	flushout(&errout);
}