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
 int /*<<< orphan*/  cmdloop (int /*<<< orphan*/ ) ; 
 char* commandname ; 
 int /*<<< orphan*/  error (char*) ; 
 int exitstatus ; 
 char* find_dot_file (char*) ; 
 int /*<<< orphan*/  popfile () ; 
 int /*<<< orphan*/  setinputfile (char*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 

int
dotcmd(int argc, char **argv)
{
	char *filename, *fullname;

	if (argc < 2)
		error("missing filename");

	exitstatus = 0;

	/*
	 * Because we have historically not supported any options,
	 * only treat "--" specially.
	 */
	filename = argc > 2 && strcmp(argv[1], "--") == 0 ? argv[2] : argv[1];

	fullname = find_dot_file(filename);
	setinputfile(fullname, 1);
	commandname = fullname;
	cmdloop(0);
	popfile();
	return exitstatus;
}