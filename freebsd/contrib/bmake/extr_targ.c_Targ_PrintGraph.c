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
 int /*<<< orphan*/  Dir_PrintDirectories () ; 
 int /*<<< orphan*/  Lst_ForEach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  Suff_PrintAll () ; 
 int /*<<< orphan*/  TargPrintOnlySrc ; 
 int /*<<< orphan*/  Targ_PrintNode ; 
 int /*<<< orphan*/  VAR_CMD ; 
 int /*<<< orphan*/  VAR_GLOBAL ; 
 int /*<<< orphan*/  Var_Dump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  allTargets ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 

void
Targ_PrintGraph(int pass)
{
    fprintf(debug_file, "#*** Input graph:\n");
    Lst_ForEach(allTargets, Targ_PrintNode, &pass);
    fprintf(debug_file, "\n\n");
    fprintf(debug_file, "#\n#   Files that are only sources:\n");
    Lst_ForEach(allTargets, TargPrintOnlySrc, NULL);
    fprintf(debug_file, "#*** Global Variables:\n");
    Var_Dump(VAR_GLOBAL);
    fprintf(debug_file, "#*** Command-line Variables:\n");
    Var_Dump(VAR_CMD);
    fprintf(debug_file, "\n");
    Dir_PrintDirectories();
    fprintf(debug_file, "\n");
    Suff_PrintAll();
}