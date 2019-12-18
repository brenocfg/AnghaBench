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
 scalar_t__ Eflag ; 
 scalar_t__ Vflag ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  getgid () ; 
 int /*<<< orphan*/  getuid () ; 
 scalar_t__* optval ; 
 scalar_t__ privileged ; 
 int setgid (int /*<<< orphan*/ ) ; 
 int setuid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
setoptionbyindex(int idx, int val)
{
	if (&optval[idx] == &privileged && !val && privileged) {
		if (setgid(getgid()) == -1)
			error("setgid");
		if (setuid(getuid()) == -1)
			error("setuid");
	}
	optval[idx] = val;
	if (val) {
		/* #%$ hack for ksh semantics */
		if (&optval[idx] == &Vflag)
			Eflag = 0;
		else if (&optval[idx] == &Eflag)
			Vflag = 0;
	}
}