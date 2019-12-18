#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int flags; int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ Var ;
struct TYPE_14__ {char* name; } ;
typedef  TYPE_2__ GNode ;

/* Variables and functions */
 int /*<<< orphan*/  Buf_AddBytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  Buf_Empty (int /*<<< orphan*/ *) ; 
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEOVERRIDES ; 
 int /*<<< orphan*/  SAVE_DOLLARS ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VAR ; 
 int /*<<< orphan*/  VARF_WANTRES ; 
 TYPE_2__* VAR_CMD ; 
 int VAR_EXPORTED ; 
 int /*<<< orphan*/  VAR_EXPORT_PARENT ; 
 int VAR_FROM_CMD ; 
 TYPE_2__* VAR_GLOBAL ; 
 int VAR_NO_EXPORT ; 
 int /*<<< orphan*/  VarAdd (char const*,char const*,TYPE_2__*) ; 
 TYPE_1__* VarFind (char const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VarFreeEnv (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  Var_Append (int /*<<< orphan*/ ,char const*,TYPE_2__*) ; 
 int /*<<< orphan*/  Var_Delete (char const*,TYPE_2__*) ; 
 int /*<<< orphan*/  Var_Export1 (char const*,int /*<<< orphan*/ ) ; 
 char* Var_Subst (int /*<<< orphan*/ *,char const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char const*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  s2Boolean (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_dollars ; 
 int /*<<< orphan*/  setenv (char const*,char const*,int) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ varNoExportEnv ; 

void
Var_Set(const char *name, const char *val, GNode *ctxt, int flags)
{
    Var   *v;
    char *expanded_name = NULL;

    /*
     * We only look for a variable in the given context since anything set
     * here will override anything in a lower context, so there's not much
     * point in searching them all just to save a bit of memory...
     */
    if (strchr(name, '$') != NULL) {
	expanded_name = Var_Subst(NULL, name, ctxt, VARF_WANTRES);
	if (expanded_name[0] == 0) {
	    if (DEBUG(VAR)) {
		fprintf(debug_file, "Var_Set(\"%s\", \"%s\", ...) "
			"name expands to empty string - ignored\n",
			name, val);
	    }
	    free(expanded_name);
	    return;
	}
	name = expanded_name;
    }
    if (ctxt == VAR_GLOBAL) {
	v = VarFind(name, VAR_CMD, 0);
	if (v != NULL) {
	    if ((v->flags & VAR_FROM_CMD)) {
		if (DEBUG(VAR)) {
		    fprintf(debug_file, "%s:%s = %s ignored!\n", ctxt->name, name, val);
		}
		goto out;
	    }
	    VarFreeEnv(v, TRUE);
	}
    }
    v = VarFind(name, ctxt, 0);
    if (v == NULL) {
	if (ctxt == VAR_CMD && (flags & VAR_NO_EXPORT) == 0) {
	    /*
	     * This var would normally prevent the same name being added
	     * to VAR_GLOBAL, so delete it from there if needed.
	     * Otherwise -V name may show the wrong value.
	     */
	    Var_Delete(name, VAR_GLOBAL);
	}
	VarAdd(name, val, ctxt);
    } else {
	Buf_Empty(&v->val);
	if (val)
	    Buf_AddBytes(&v->val, strlen(val), val);

	if (DEBUG(VAR)) {
	    fprintf(debug_file, "%s:%s = %s\n", ctxt->name, name, val);
	}
	if ((v->flags & VAR_EXPORTED)) {
	    Var_Export1(name, VAR_EXPORT_PARENT);
	}
    }
    /*
     * Any variables given on the command line are automatically exported
     * to the environment (as per POSIX standard)
     */
    if (ctxt == VAR_CMD && (flags & VAR_NO_EXPORT) == 0) {
	if (v == NULL) {
	    /* we just added it */
	    v = VarFind(name, ctxt, 0);
	}
	if (v != NULL)
	    v->flags |= VAR_FROM_CMD;
	/*
	 * If requested, don't export these in the environment
	 * individually.  We still put them in MAKEOVERRIDES so
	 * that the command-line settings continue to override
	 * Makefile settings.
	 */
	if (varNoExportEnv != TRUE)
	    setenv(name, val ? val : "", 1);

	Var_Append(MAKEOVERRIDES, name, VAR_GLOBAL);
    }
    if (*name == '.') {
	if (strcmp(name, SAVE_DOLLARS) == 0)
	    save_dollars = s2Boolean(val, save_dollars);
    }

 out:
    free(expanded_name);
    if (v != NULL)
	VarFreeEnv(v, TRUE);
}