#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ar_hdr {int /*<<< orphan*/  AR_DATE; } ;
struct TYPE_5__ {int type; scalar_t__ mtime; TYPE_1__* cmgn; int /*<<< orphan*/  path; int /*<<< orphan*/  children; } ;
struct TYPE_4__ {scalar_t__ mtime; } ;
typedef  TYPE_2__ GNode ;
typedef  int Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  ARCH ; 
 struct ar_hdr* ArchStatMember (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 scalar_t__ Lst_IsEmpty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKE ; 
 scalar_t__ OP_NOP (int) ; 
 int OP_PHONY ; 
 char* RANLIBMAG ; 
 int TRUE ; 
 char* Targ_FmtTime (int) ; 
 int /*<<< orphan*/  UNCONST (char*) ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ now ; 
 scalar_t__ strtol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

Boolean
Arch_LibOODate(GNode *gn)
{
    Boolean 	  oodate;

    if (gn->type & OP_PHONY) {
	oodate = TRUE;
    } else if (OP_NOP(gn->type) && Lst_IsEmpty(gn->children)) {
	oodate = FALSE;
    } else if ((!Lst_IsEmpty(gn->children) && gn->cmgn == NULL) ||
	       (gn->mtime > now) ||
	       (gn->cmgn != NULL && gn->mtime < gn->cmgn->mtime)) {
	oodate = TRUE;
    } else {
#ifdef RANLIBMAG
	struct ar_hdr  	*arhPtr;    /* Header for __.SYMDEF */
	int 	  	modTimeTOC; /* The table-of-contents's mod time */

	arhPtr = ArchStatMember(gn->path, UNCONST(RANLIBMAG), FALSE);

	if (arhPtr != NULL) {
	    modTimeTOC = (int)strtol(arhPtr->AR_DATE, NULL, 10);

	    if (DEBUG(ARCH) || DEBUG(MAKE)) {
		fprintf(debug_file, "%s modified %s...", RANLIBMAG, Targ_FmtTime(modTimeTOC));
	    }
	    oodate = (gn->cmgn == NULL || gn->cmgn->mtime > modTimeTOC);
	} else {
	    /*
	     * A library w/o a table of contents is out-of-date
	     */
	    if (DEBUG(ARCH) || DEBUG(MAKE)) {
		fprintf(debug_file, "No t.o.c....");
	    }
	    oodate = TRUE;
	}
#else
	oodate = FALSE;
#endif
    }
    return (oodate);
}