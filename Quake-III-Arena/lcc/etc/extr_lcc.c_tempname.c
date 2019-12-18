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
 int /*<<< orphan*/  append (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * com ; 
 int /*<<< orphan*/  getpid () ; 
 char* replace (char*,char,char) ; 
 int /*<<< orphan*/  rmlist ; 
 char* stringf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tempdir ; 

char *tempname(char *suffix) {
	static int n;
	char *name = stringf("%s/lcc%d%d%s", tempdir, getpid(), n++, suffix);

	if (strstr(com[1], "win32") != NULL)
		name = replace(name, '/', '\\');
	rmlist = append(name, rmlist);
	return name;
}