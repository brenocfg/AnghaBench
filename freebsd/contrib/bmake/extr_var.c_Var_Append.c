#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int flags; int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ Var ;
struct TYPE_12__ {char* name; int /*<<< orphan*/  context; } ;
typedef  int /*<<< orphan*/  Hash_Entry ;
typedef  TYPE_2__ GNode ;

/* Variables and functions */
 int /*<<< orphan*/  Buf_AddByte (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  Buf_AddBytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 char* Buf_GetAll (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 int FIND_CMD ; 
 int FIND_ENV ; 
 int /*<<< orphan*/ * Hash_CreateEntry (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Hash_SetValue (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  VAR ; 
 int /*<<< orphan*/  VARF_WANTRES ; 
 TYPE_2__* VAR_CMD ; 
 int VAR_FROM_CMD ; 
 int VAR_FROM_ENV ; 
 TYPE_2__* VAR_GLOBAL ; 
 TYPE_1__* VarFind (char const*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  Var_Set (char const*,char const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 char* Var_Subst (int /*<<< orphan*/ *,char const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char const*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void
Var_Append(const char *name, const char *val, GNode *ctxt)
{
    Var		   *v;
    Hash_Entry	   *h;
    char *expanded_name = NULL;

    if (strchr(name, '$') != NULL) {
	expanded_name = Var_Subst(NULL, name, ctxt, VARF_WANTRES);
	if (expanded_name[0] == 0) {
	    if (DEBUG(VAR)) {
		fprintf(debug_file, "Var_Append(\"%s\", \"%s\", ...) "
			"name expands to empty string - ignored\n",
			name, val);
	    }
	    free(expanded_name);
	    return;
	}
	name = expanded_name;
    }

    v = VarFind(name, ctxt, (ctxt == VAR_GLOBAL) ? (FIND_CMD|FIND_ENV) : 0);

    if (v == NULL) {
	Var_Set(name, val, ctxt, 0);
    } else if (ctxt == VAR_CMD || !(v->flags & VAR_FROM_CMD)) {
	Buf_AddByte(&v->val, ' ');
	Buf_AddBytes(&v->val, strlen(val), val);

	if (DEBUG(VAR)) {
	    fprintf(debug_file, "%s:%s = %s\n", ctxt->name, name,
		   Buf_GetAll(&v->val, NULL));
	}

	if (v->flags & VAR_FROM_ENV) {
	    /*
	     * If the original variable came from the environment, we
	     * have to install it in the global context (we could place
	     * it in the environment, but then we should provide a way to
	     * export other variables...)
	     */
	    v->flags &= ~VAR_FROM_ENV;
	    h = Hash_CreateEntry(&ctxt->context, name, NULL);
	    Hash_SetValue(h, v);
	}
    }
    free(expanded_name);
}