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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/ * LstNode ;
typedef  scalar_t__ Boolean ;

/* Variables and functions */
 scalar_t__ EXPAND_VARS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  Fatal (char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ Lst_Datum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Lst_First (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Lst_Succ (int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VARF_WANTRES ; 
 int /*<<< orphan*/  VAR_GLOBAL ; 
 char* Var_Subst (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* Var_Value (char*,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ debugVflag ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ getBoolean (char*,scalar_t__) ; 
 scalar_t__ printVars ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  progname ; 
 int snprintf (char*,int,char*,char*) ; 
 scalar_t__ strchr (char*,char) ; 
 int /*<<< orphan*/  variables ; 

__attribute__((used)) static void
doPrintVars(void)
{
	LstNode ln;
	Boolean expandVars;

	if (printVars == EXPAND_VARS)
		expandVars = TRUE;
	else if (debugVflag)
		expandVars = FALSE;
	else
		expandVars = getBoolean(".MAKE.EXPAND_VARIABLES", FALSE);

	for (ln = Lst_First(variables); ln != NULL;
	    ln = Lst_Succ(ln)) {
		char *var = (char *)Lst_Datum(ln);
		char *value;
		char *p1;
		
		if (strchr(var, '$')) {
			value = p1 = Var_Subst(NULL, var, VAR_GLOBAL,
			    VARF_WANTRES);
		} else if (expandVars) {
			char tmp[128];
			int len = snprintf(tmp, sizeof(tmp), "${%s}", var);
							
			if (len >= (int)sizeof(tmp))
				Fatal("%s: variable name too big: %s",
				    progname, var);
			value = p1 = Var_Subst(NULL, tmp, VAR_GLOBAL,
			    VARF_WANTRES);
		} else {
			value = Var_Value(var, VAR_GLOBAL, &p1);
		}
		printf("%s\n", value ? value : "");
		free(p1);
	}
}