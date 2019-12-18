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
 int exitstatus ; 
 int /*<<< orphan*/  out2fmt_flush (char*,char*) ; 

int
bltincmd(int argc, char **argv)
{
	if (argc > 1) {
		out2fmt_flush("%s: not found\n", argv[1]);
		return 127;
	}
	/*
	 * Preserve exitstatus of a previous possible command substitution
	 * as POSIX mandates
	 */
	return exitstatus;
}