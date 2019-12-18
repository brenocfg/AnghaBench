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
 int complement ; 
 scalar_t__ delcount ; 
 int exitstat ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int linenum ; 
 scalar_t__ lnblank ; 
 scalar_t__ lnnum ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ symlist ; 
 int /*<<< orphan*/  tline ; 

__attribute__((used)) static void
flushline(bool keep)
{
	if (symlist)
		return;
	if (keep ^ complement) {
		if (lnnum && delcount > 0)
			printf("#line %d\n", linenum);
		fputs(tline, stdout);
		delcount = 0;
	} else {
		if (lnblank)
			putc('\n', stdout);
		exitstat = 1;
		delcount += 1;
	}
}