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
 int EXPORTCMD ; 
 int SETCMD ; 
 int TRAPCMD ; 
 int ULIMITCMD ; 
 int UMASKCMD ; 
 scalar_t__ safe_builtin_always (int) ; 

__attribute__((used)) static int
safe_builtin(int idx, int argc, char **argv)
{
	/* Generated from builtins.def. */
	if (safe_builtin_always(idx))
		return (1);
	if (idx == EXPORTCMD || idx == TRAPCMD || idx == ULIMITCMD ||
	    idx == UMASKCMD)
		return (argc <= 1 || (argc == 2 && argv[1][0] == '-'));
	if (idx == SETCMD)
		return (argc <= 1 || (argc == 2 && (argv[1][0] == '-' ||
		    argv[1][0] == '+') && argv[1][1] == 'o' &&
		    argv[1][2] == '\0'));
	return (0);
}