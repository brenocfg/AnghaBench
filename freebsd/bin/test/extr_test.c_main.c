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
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  error (char*) ; 
 int nargc ; 
 int oexpr (int /*<<< orphan*/ ) ; 
 scalar_t__ parenlevel ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  syntax (char*,char*) ; 
 int /*<<< orphan*/  t_lex (char*) ; 
 char** t_wp ; 

int
main(int argc, char **argv)
{
	int	res;
	char	*p;

	if ((p = strrchr(argv[0], '/')) == NULL)
		p = argv[0];
	else
		p++;
	if (strcmp(p, "[") == 0) {
		if (strcmp(argv[--argc], "]") != 0)
			error("missing ]");
		argv[argc] = NULL;
	}

	/* no expression => false */
	if (--argc <= 0)
		return 1;

#ifndef SHELL
	(void)setlocale(LC_CTYPE, "");
#endif
	nargc = argc;
	t_wp = &argv[1];
	parenlevel = 0;
	if (nargc == 4 && strcmp(*t_wp, "!") == 0) {
		/* Things like ! "" -o x do not fit in the normal grammar. */
		--nargc;
		++t_wp;
		res = oexpr(t_lex(*t_wp));
	} else
		res = !oexpr(t_lex(*t_wp));

	if (--nargc > 0)
		syntax(*t_wp, "unexpected operator");

	return res;
}