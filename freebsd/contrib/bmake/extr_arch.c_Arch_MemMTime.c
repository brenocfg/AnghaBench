#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_4__ {int type; char* name; int flags; int /*<<< orphan*/  mtime; int /*<<< orphan*/  parents; } ;
typedef  int /*<<< orphan*/ * LstNode ;
typedef  TYPE_1__ GNode ;

/* Variables and functions */
 int /*<<< orphan*/  Arch_MTime (TYPE_1__*) ; 
 int /*<<< orphan*/  Lst_Close (int /*<<< orphan*/ ) ; 
 scalar_t__ Lst_Datum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Lst_Next (int /*<<< orphan*/ ) ; 
 scalar_t__ Lst_Open (int /*<<< orphan*/ ) ; 
 int OP_ARCHV ; 
 int REMAKE ; 
 scalar_t__ SUCCESS ; 
 char* strchr (char*,char) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

time_t
Arch_MemMTime(GNode *gn)
{
    LstNode 	  ln;
    GNode   	  *pgn;
    char    	  *nameStart,
		  *nameEnd;

    if (Lst_Open(gn->parents) != SUCCESS) {
	gn->mtime = 0;
	return (0);
    }
    while ((ln = Lst_Next(gn->parents)) != NULL) {
	pgn = (GNode *)Lst_Datum(ln);

	if (pgn->type & OP_ARCHV) {
	    /*
	     * If the parent is an archive specification and is being made
	     * and its member's name matches the name of the node we were
	     * given, record the modification time of the parent in the
	     * child. We keep searching its parents in case some other
	     * parent requires this child to exist...
	     */
	    nameStart = strchr(pgn->name, '(') + 1;
	    nameEnd = strchr(nameStart, ')');

	    if ((pgn->flags & REMAKE) &&
		strncmp(nameStart, gn->name, nameEnd - nameStart) == 0) {
				     gn->mtime = Arch_MTime(pgn);
	    }
	} else if (pgn->flags & REMAKE) {
	    /*
	     * Something which isn't a library depends on the existence of
	     * this target, so it needs to exist.
	     */
	    gn->mtime = 0;
	    break;
	}
    }

    Lst_Close(gn->parents);

    return (gn->mtime);
}