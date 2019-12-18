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
typedef  int /*<<< orphan*/  Var ;
typedef  int /*<<< orphan*/  GNode ;
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int FIND_CMD ; 
 int FIND_ENV ; 
 int FIND_GLOBAL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VARF_WANTRES ; 
 int /*<<< orphan*/ * VarFind (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VarFreeEnv (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* Var_Subst (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strchr (char const*,char) ; 

Boolean
Var_Exists(const char *name, GNode *ctxt)
{
    Var		  *v;
    char          *cp;

    if ((cp = strchr(name, '$')) != NULL) {
	cp = Var_Subst(NULL, name, ctxt, VARF_WANTRES);
    }
    v = VarFind(cp ? cp : name, ctxt, FIND_CMD|FIND_GLOBAL|FIND_ENV);
    free(cp);
    if (v == NULL) {
	return(FALSE);
    } else {
	(void)VarFreeEnv(v, TRUE);
    }
    return(TRUE);
}