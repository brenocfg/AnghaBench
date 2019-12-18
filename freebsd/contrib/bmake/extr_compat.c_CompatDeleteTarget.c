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
typedef  int /*<<< orphan*/  GNode ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*,char*) ; 
 int /*<<< orphan*/  TARGET ; 
 int /*<<< orphan*/  Targ_Precious (int /*<<< orphan*/ *) ; 
 char* Var_Value (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char**) ; 
 int eunlink (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  noExecute ; 

__attribute__((used)) static void
CompatDeleteTarget(GNode *gn)
{
    if ((gn != NULL) && !Targ_Precious (gn)) {
	char	  *p1;
	char 	  *file = Var_Value(TARGET, gn, &p1);

	if (!noExecute && eunlink(file) != -1) {
	    Error("*** %s removed", file);
	}

	free(p1);
    }
}