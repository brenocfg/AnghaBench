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
 int /*<<< orphan*/  STDOUT_FILENO ; 
 char* getenv (char*) ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
do_color_from_env(void)
{
	const char *p;
	bool doit;

	doit = false;
	p = getenv("CLICOLOR");
	if (p == NULL) {
		/*
		 * COLORTERM is the more standard name for this variable.  We'll
		 * honor it as long as it's both set and not empty.
		 */
		p = getenv("COLORTERM");
		if (p != NULL && *p != '\0')
			doit = true;
	} else
		doit = true;

	return (doit &&
	    (isatty(STDOUT_FILENO) || getenv("CLICOLOR_FORCE")));
}