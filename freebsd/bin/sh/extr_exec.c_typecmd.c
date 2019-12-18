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
 int /*<<< orphan*/  TYPECMD_TYPE ; 
 int /*<<< orphan*/  bltinlookup (char*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int typecmd_impl (int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
typecmd(int argc, char **argv)
{
	if (argc > 2 && strcmp(argv[1], "--") == 0)
		argc--, argv++;
	return typecmd_impl(argc, argv, TYPECMD_TYPE, bltinlookup("PATH", 1));
}