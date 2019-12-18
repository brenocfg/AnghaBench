#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_7__ {int /*<<< orphan*/  type; int /*<<< orphan*/  commands; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ GNode ;

/* Variables and functions */
 int /*<<< orphan*/  Compat_Make (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  Lst_ForEach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  OP_SPECIAL ; 
 int /*<<< orphan*/  TARG_NOCREATE ; 
 TYPE_1__* Targ_FindNode (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VARF_WANTRES ; 
 int /*<<< orphan*/  VAR_GLOBAL ; 
 int /*<<< orphan*/  Var_Delete (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Var_Set (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* Var_Subst (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addErrorCMD ; 
 char* curdir ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 char* progname ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

void
PrintOnError(GNode *gn, const char *s)
{
    static GNode *en = NULL;
    char tmp[64];
    char *cp;

    if (s)
	printf("%s", s);
	
    printf("\n%s: stopped in %s\n", progname, curdir);

    if (en)
	return;				/* we've been here! */
    if (gn) {
	/*
	 * We can print this even if there is no .ERROR target.
	 */
	Var_Set(".ERROR_TARGET", gn->name, VAR_GLOBAL, 0);
	Var_Delete(".ERROR_CMD", VAR_GLOBAL);
	Lst_ForEach(gn->commands, addErrorCMD, gn);
    }
    strncpy(tmp, "${MAKE_PRINT_VAR_ON_ERROR:@v@$v='${$v}'\n@}",
	    sizeof(tmp) - 1);
    cp = Var_Subst(NULL, tmp, VAR_GLOBAL, VARF_WANTRES);
    if (cp) {
	if (*cp)
	    printf("%s", cp);
	free(cp);
    }
    fflush(stdout);

    /*
     * Finally, see if there is a .ERROR target, and run it if so.
     */
    en = Targ_FindNode(".ERROR", TARG_NOCREATE);
    if (en) {
	en->type |= OP_SPECIAL;
	Compat_Make(en, en);
    }
}