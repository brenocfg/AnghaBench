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
typedef  int /*<<< orphan*/ * LstNode ;
typedef  int /*<<< orphan*/  Lst ;
typedef  int /*<<< orphan*/  GNode ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*,char*) ; 
 scalar_t__ FAILURE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Lst_AtEnd (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lst_Close (int /*<<< orphan*/ ) ; 
 scalar_t__ Lst_Datum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lst_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Lst_Next (int /*<<< orphan*/ ) ; 
 scalar_t__ Lst_Open (int /*<<< orphan*/ ) ; 
 int TARG_NOCREATE ; 
 int /*<<< orphan*/ * Targ_FindNode (char*,int) ; 

Lst
Targ_FindList(Lst names, int flags)
{
    Lst            nodes;	/* result list */
    LstNode	   ln;		/* name list element */
    GNode	   *gn;		/* node in tLn */
    char    	   *name;

    nodes = Lst_Init(FALSE);

    if (Lst_Open(names) == FAILURE) {
	return (nodes);
    }
    while ((ln = Lst_Next(names)) != NULL) {
	name = (char *)Lst_Datum(ln);
	gn = Targ_FindNode(name, flags);
	if (gn != NULL) {
	    /*
	     * Note: Lst_AtEnd must come before the Lst_Concat so the nodes
	     * are added to the list in the order in which they were
	     * encountered in the makefile.
	     */
	    (void)Lst_AtEnd(nodes, gn);
	} else if (flags == TARG_NOCREATE) {
	    Error("\"%s\" -- target unknown.", name);
	}
    }
    Lst_Close(names);
    return (nodes);
}