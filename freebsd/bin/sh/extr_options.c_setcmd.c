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
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 char** argptr ; 
 int /*<<< orphan*/  options (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optschanged () ; 
 int /*<<< orphan*/  setparam (int,char**) ; 
 int showvarscmd (int,char**) ; 

int
setcmd(int argc, char **argv)
{
	if (argc == 1)
		return showvarscmd(argc, argv);
	INTOFF;
	options(0);
	optschanged();
	if (*argptr != NULL) {
		setparam(argc - (argptr - argv), argptr);
	}
	INTON;
	return 0;
}