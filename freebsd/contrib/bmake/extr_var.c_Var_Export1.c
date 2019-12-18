#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ Var ;

/* Variables and functions */
 int BUFSIZ ; 
 char* Buf_GetAll (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VARF_WANTRES ; 
 int VAR_EXPORTED ; 
 int VAR_EXPORT_LITERAL ; 
 int VAR_EXPORT_PARENT ; 
 int /*<<< orphan*/  VAR_GLOBAL ; 
 int VAR_IN_USE ; 
 int VAR_REEXPORT ; 
 TYPE_1__* VarFind (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* Var_Subst (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  setenv (char const*,char*,int) ; 
 int snprintf (char*,int,char*,char const*) ; 
 scalar_t__ strchr (char*,char) ; 

__attribute__((used)) static int
Var_Export1(const char *name, int flags)
{
    char tmp[BUFSIZ];
    Var *v;
    char *val = NULL;
    int n;
    int parent = (flags & VAR_EXPORT_PARENT);

    if (*name == '.')
	return 0;			/* skip internals */
    if (!name[1]) {
	/*
	 * A single char.
	 * If it is one of the vars that should only appear in
	 * local context, skip it, else we can get Var_Subst
	 * into a loop.
	 */
	switch (name[0]) {
	case '@':
	case '%':
	case '*':
	case '!':
	    return 0;
	}
    }
    v = VarFind(name, VAR_GLOBAL, 0);
    if (v == NULL) {
	return 0;
    }
    if (!parent &&
	(v->flags & (VAR_EXPORTED|VAR_REEXPORT)) == VAR_EXPORTED) {
	return 0;			/* nothing to do */
    }
    val = Buf_GetAll(&v->val, NULL);
    if ((flags & VAR_EXPORT_LITERAL) == 0 && strchr(val, '$')) {
	if (parent) {
	    /*
	     * Flag this as something we need to re-export.
	     * No point actually exporting it now though,
	     * the child can do it at the last minute.
	     */
	    v->flags |= (VAR_EXPORTED|VAR_REEXPORT);
	    return 1;
	}
	if (v->flags & VAR_IN_USE) {
	    /*
	     * We recursed while exporting in a child.
	     * This isn't going to end well, just skip it.
	     */
	    return 0;
	}
	n = snprintf(tmp, sizeof(tmp), "${%s}", name);
	if (n < (int)sizeof(tmp)) {
	    val = Var_Subst(NULL, tmp, VAR_GLOBAL, VARF_WANTRES);
	    setenv(name, val, 1);
	    free(val);
	}
    } else {
	if (parent) {
	    v->flags &= ~VAR_REEXPORT;	/* once will do */
	}
	if (parent || !(v->flags & VAR_EXPORTED)) {
	    setenv(name, val, 1);
	}
    }
    /*
     * This is so Var_Set knows to call Var_Export again...
     */
    if (parent) {
	v->flags |= VAR_EXPORTED;
    }
    return 1;
}