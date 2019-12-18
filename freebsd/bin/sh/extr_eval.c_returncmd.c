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
 int /*<<< orphan*/  SKIPRETURN ; 
 int /*<<< orphan*/  evalskip ; 
 int number (char*) ; 
 int oexitstatus ; 
 int skipcount ; 

int
returncmd(int argc, char **argv)
{
	int ret = argc > 1 ? number(argv[1]) : oexitstatus;

	evalskip = SKIPRETURN;
	skipcount = 1;
	return ret;
}