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
 int /*<<< orphan*/  __init_libc (char**,char*) ; 
 int /*<<< orphan*/  __libc_start_init () ; 
 int /*<<< orphan*/  exit (int) ; 

int __libc_start_main(int (*main)(int,char **,char **), int argc, char **argv)
{
	char **envp = argv+argc+1;

	__init_libc(envp, argv[0]);
	__libc_start_init();

	/* Pass control to the application */
	exit(main(argc, argv, envp));
	return 0;
}