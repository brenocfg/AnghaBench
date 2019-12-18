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
struct TYPE_3__ {char* name; int cohort_num; int flags; int type; scalar_t__ made; int unmade; scalar_t__ mtime; int /*<<< orphan*/  cohorts; int /*<<< orphan*/  commands; int /*<<< orphan*/  children; int /*<<< orphan*/  order_succ; int /*<<< orphan*/  order_pred; int /*<<< orphan*/  parents; int /*<<< orphan*/  iParents; } ;
typedef  TYPE_1__ GNode ;

/* Variables and functions */
 int /*<<< orphan*/  Lst_ForEach (int /*<<< orphan*/ ,int (*) (void*,void*),int*) ; 
 int /*<<< orphan*/  Lst_IsEmpty (int /*<<< orphan*/ ) ; 
#define  OP_DEPENDS 130 
#define  OP_DOUBLEDEP 129 
 int OP_EXEC ; 
#define  OP_FORCE 128 
 int OP_JOIN ; 
 int /*<<< orphan*/  OP_NOP (int) ; 
 int OP_OPMASK ; 
 int OP_USE ; 
 int OP_USEBEFORE ; 
 int TargPrintName (void*,void*) ; 
 char* Targ_FmtTime (scalar_t__) ; 
 int Targ_PrintCmd (void*,void*) ; 
 int /*<<< orphan*/  Targ_PrintType (int) ; 
 scalar_t__ UNMADE ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* made_name (scalar_t__) ; 
 TYPE_1__* mainTarg ; 

int
Targ_PrintNode(void *gnp, void *passp)
{
    GNode         *gn = (GNode *)gnp;
    int	    	  pass = passp ? *(int *)passp : 0;

    fprintf(debug_file, "# %s%s, flags %x, type %x, made %d\n",
	    gn->name, gn->cohort_num, gn->flags, gn->type, gn->made);
    if (gn->flags == 0)
	return 0;

    if (!OP_NOP(gn->type)) {
	fprintf(debug_file, "#\n");
	if (gn == mainTarg) {
	    fprintf(debug_file, "# *** MAIN TARGET ***\n");
	}
	if (pass >= 2) {
	    if (gn->unmade) {
		fprintf(debug_file, "# %d unmade children\n", gn->unmade);
	    } else {
		fprintf(debug_file, "# No unmade children\n");
	    }
	    if (! (gn->type & (OP_JOIN|OP_USE|OP_USEBEFORE|OP_EXEC))) {
		if (gn->mtime != 0) {
		    fprintf(debug_file, "# last modified %s: %s\n",
			      Targ_FmtTime(gn->mtime),
			      made_name(gn->made));
		} else if (gn->made != UNMADE) {
		    fprintf(debug_file, "# non-existent (maybe): %s\n",
			      made_name(gn->made));
		} else {
		    fprintf(debug_file, "# unmade\n");
		}
	    }
	    if (!Lst_IsEmpty (gn->iParents)) {
		fprintf(debug_file, "# implicit parents: ");
		Lst_ForEach(gn->iParents, TargPrintName, NULL);
		fprintf(debug_file, "\n");
	    }
	} else {
	    if (gn->unmade)
		fprintf(debug_file, "# %d unmade children\n", gn->unmade);
	}
	if (!Lst_IsEmpty (gn->parents)) {
	    fprintf(debug_file, "# parents: ");
	    Lst_ForEach(gn->parents, TargPrintName, NULL);
	    fprintf(debug_file, "\n");
	}
	if (!Lst_IsEmpty (gn->order_pred)) {
	    fprintf(debug_file, "# order_pred: ");
	    Lst_ForEach(gn->order_pred, TargPrintName, NULL);
	    fprintf(debug_file, "\n");
	}
	if (!Lst_IsEmpty (gn->order_succ)) {
	    fprintf(debug_file, "# order_succ: ");
	    Lst_ForEach(gn->order_succ, TargPrintName, NULL);
	    fprintf(debug_file, "\n");
	}

	fprintf(debug_file, "%-16s", gn->name);
	switch (gn->type & OP_OPMASK) {
	    case OP_DEPENDS:
		fprintf(debug_file, ": "); break;
	    case OP_FORCE:
		fprintf(debug_file, "! "); break;
	    case OP_DOUBLEDEP:
		fprintf(debug_file, ":: "); break;
	}
	Targ_PrintType(gn->type);
	Lst_ForEach(gn->children, TargPrintName, NULL);
	fprintf(debug_file, "\n");
	Lst_ForEach(gn->commands, Targ_PrintCmd, NULL);
	fprintf(debug_file, "\n\n");
	if (gn->type & OP_DOUBLEDEP) {
	    Lst_ForEach(gn->cohorts, Targ_PrintNode, &pass);
	}
    }
    return (0);
}