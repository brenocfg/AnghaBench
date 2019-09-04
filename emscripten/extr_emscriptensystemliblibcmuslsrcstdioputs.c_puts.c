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
 int /*<<< orphan*/  FLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FUNLOCK (int /*<<< orphan*/ ) ; 
 scalar_t__ fputs (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ putc_unlocked (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

int puts(const char *s)
{
	int r;
	FLOCK(stdout);
	r = -(fputs(s, stdout) < 0 || putc_unlocked('\n', stdout) < 0);
	FUNLOCK(stdout);
	return r;
}