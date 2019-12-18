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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int sys_nsig ; 
 char** sys_signame ; 

__attribute__((used)) static void
printsignals(FILE *fp)
{
	int n;

	for (n = 1; n < sys_nsig; n++) {
		(void)fprintf(fp, "%s", sys_signame[n]);
		if (n == (sys_nsig / 2) || n == (sys_nsig - 1))
			(void)fprintf(fp, "\n");
		else
			(void)fprintf(fp, " ");
	}
}