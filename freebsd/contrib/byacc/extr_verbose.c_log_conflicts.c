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
 char* PLURAL (int) ; 
 int* RRconflicts ; 
 int* SRconflicts ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int nstates ; 
 int /*<<< orphan*/  verbose_file ; 

__attribute__((used)) static void
log_conflicts(void)
{
    int i;

    fprintf(verbose_file, "\n\n");
    for (i = 0; i < nstates; i++)
    {
	if (SRconflicts[i] || RRconflicts[i])
	{
	    fprintf(verbose_file, "State %d contains ", i);
	    if (SRconflicts[i] > 0)
		fprintf(verbose_file, "%d shift/reduce conflict%s",
			SRconflicts[i],
			PLURAL(SRconflicts[i]));
	    if (SRconflicts[i] && RRconflicts[i])
		fprintf(verbose_file, ", ");
	    if (RRconflicts[i] > 0)
		fprintf(verbose_file, "%d reduce/reduce conflict%s",
			RRconflicts[i],
			PLURAL(RRconflicts[i]));
	    fprintf(verbose_file, ".\n");
	}
    }
}