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
struct procstat {char* cmd; } ;
struct job {int nprocs; struct procstat* ps; } ;

/* Variables and functions */
 int /*<<< orphan*/  out1c (char) ; 
 int /*<<< orphan*/  out1str (char*) ; 

__attribute__((used)) static void
printjobcmd(struct job *jp)
{
	struct procstat *ps;
	int i;

	for (ps = jp->ps, i = jp->nprocs ; --i >= 0 ; ps++) {
		out1str(ps->cmd);
		if (i > 0)
			out1str(" | ");
	}
	out1c('\n');
}