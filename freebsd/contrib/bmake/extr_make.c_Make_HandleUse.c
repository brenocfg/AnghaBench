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
struct TYPE_7__ {int type; char* name; char* uname; int unmade; int /*<<< orphan*/  children; int /*<<< orphan*/  parents; int /*<<< orphan*/  commands; } ;
typedef  int /*<<< orphan*/ * LstNode ;
typedef  int /*<<< orphan*/  Lst ;
typedef  TYPE_1__ GNode ;

/* Variables and functions */
 int /*<<< orphan*/  LST_CONCNEW ; 
 int /*<<< orphan*/  Lst_AtEnd (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Lst_Close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_Concat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ Lst_Datum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lst_Destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lst_Duplicate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ Lst_IsEmpty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Lst_Next (int /*<<< orphan*/ ) ; 
 scalar_t__ Lst_Open (int /*<<< orphan*/ ) ; 
 int OP_OPMASK ; 
 int OP_TRANSFORM ; 
 int OP_USE ; 
 int OP_USEBEFORE ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  TARG_NOCREATE ; 
 TYPE_1__* Targ_FindNode (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VARF_WANTRES ; 
 char* Var_Subst (int /*<<< orphan*/ *,char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

void
Make_HandleUse(GNode *cgn, GNode *pgn)
{
    LstNode	ln; 	/* An element in the children list */

#ifdef DEBUG_SRC
    if ((cgn->type & (OP_USE|OP_USEBEFORE|OP_TRANSFORM)) == 0) {
	fprintf(debug_file, "Make_HandleUse: called for plain node %s\n", cgn->name);
	return;
    }
#endif

    if ((cgn->type & (OP_USE|OP_USEBEFORE)) || Lst_IsEmpty(pgn->commands)) {
	    if (cgn->type & OP_USEBEFORE) {
		/*
		 * .USEBEFORE --
		 *	prepend the child's commands to the parent.
		 */
		Lst cmds = pgn->commands;
		pgn->commands = Lst_Duplicate(cgn->commands, NULL);
		(void)Lst_Concat(pgn->commands, cmds, LST_CONCNEW);
		Lst_Destroy(cmds, NULL);
	    } else {
		/*
		 * .USE or target has no commands --
		 *	append the child's commands to the parent.
		 */
		(void)Lst_Concat(pgn->commands, cgn->commands, LST_CONCNEW);
	    }
    }

    if (Lst_Open(cgn->children) == SUCCESS) {
	while ((ln = Lst_Next(cgn->children)) != NULL) {
	    GNode *tgn, *gn = (GNode *)Lst_Datum(ln);

	    /*
	     * Expand variables in the .USE node's name
	     * and save the unexpanded form.
	     * We don't need to do this for commands.
	     * They get expanded properly when we execute.
	     */
	    if (gn->uname == NULL) {
		gn->uname = gn->name;
	    } else {
		free(gn->name);
	    }
	    gn->name = Var_Subst(NULL, gn->uname, pgn, VARF_WANTRES);
	    if (gn->name && gn->uname && strcmp(gn->name, gn->uname) != 0) {
		/* See if we have a target for this node. */
		tgn = Targ_FindNode(gn->name, TARG_NOCREATE);
		if (tgn != NULL)
		    gn = tgn;
	    }

	    (void)Lst_AtEnd(pgn->children, gn);
	    (void)Lst_AtEnd(gn->parents, pgn);
	    pgn->unmade += 1;
	}
	Lst_Close(cgn->children);
    }

    pgn->type |= cgn->type & ~(OP_OPMASK|OP_USE|OP_USEBEFORE|OP_TRANSFORM);
}