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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int ENOMEM ; 
 char** calloc (int,int) ; 
 scalar_t__ header_argc ; 
 char const** header_argv ; 

int
perf_header__set_cmdline(int argc, const char **argv)
{
	int i;

	/*
	 * If header_argv has already been set, do not override it.
	 * This allows a command to set the cmdline, parse args and
	 * then call another builtin function that implements a
	 * command -- e.g, cmd_kvm calling cmd_record.
	 */
	if (header_argv)
		return 0;

	header_argc = (u32)argc;

	/* do not include NULL termination */
	header_argv = calloc(argc, sizeof(char *));
	if (!header_argv)
		return -ENOMEM;

	/*
	 * must copy argv contents because it gets moved
	 * around during option parsing
	 */
	for (i = 0; i < argc ; i++)
		header_argv[i] = argv[i];

	return 0;
}