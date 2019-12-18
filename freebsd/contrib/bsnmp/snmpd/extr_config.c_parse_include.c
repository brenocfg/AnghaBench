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
 char TOK_STR ; 
 int _POSIX2_LINE_MAX ; 
 char gettoken () ; 
 int input_open_file (char*,int) ; 
 int /*<<< orphan*/  report (char*,...) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strval ; 
 char token ; 

__attribute__((used)) static void
parse_include(void)
{
	int sysdir = 0;
	char fname[_POSIX2_LINE_MAX];

	if (gettoken() == '<') {
		sysdir = 1;
		if (gettoken() != TOK_STR)
			report("expecting filename after in .include");
	} else if (token != TOK_STR)
		report("expecting filename after in .include");

	strcpy(fname, strval);
	if (sysdir && gettoken() != '>')
		report("expecting '>'");
	gettoken();
	if (input_open_file(fname, sysdir) == -1)
		report("%s: %m", fname);
}