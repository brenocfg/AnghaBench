#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* file; TYPE_1__* suff; } ;
struct TYPE_6__ {int /*<<< orphan*/  searchPath; } ;
typedef  TYPE_2__ Src ;
typedef  int /*<<< orphan*/  Lst ;

/* Variables and functions */
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 char* Dir_FindFile (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_AtEnd (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ Lst_DeQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_IsEmpty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUFF ; 
 int /*<<< orphan*/  SuffAddLevel (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  TARG_NOCREATE ; 
 int /*<<< orphan*/ * Targ_FindNode (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static Src *
SuffFindThem(Lst srcs, Lst slst)
{
    Src            *s;		/* current Src */
    Src		   *rs;		/* returned Src */
    char	   *ptr;

    rs = NULL;

    while (!Lst_IsEmpty (srcs)) {
	s = (Src *)Lst_DeQueue(srcs);

	if (DEBUG(SUFF)) {
	    fprintf(debug_file, "\ttrying %s...", s->file);
	}

	/*
	 * A file is considered to exist if either a node exists in the
	 * graph for it or the file actually exists.
	 */
	if (Targ_FindNode(s->file, TARG_NOCREATE) != NULL) {
#ifdef DEBUG_SRC
	    fprintf(debug_file, "remove %p from %p\n", s, srcs);
#endif
	    rs = s;
	    break;
	}

	if ((ptr = Dir_FindFile(s->file, s->suff->searchPath)) != NULL) {
	    rs = s;
#ifdef DEBUG_SRC
	    fprintf(debug_file, "remove %p from %p\n", s, srcs);
#endif
	    free(ptr);
	    break;
	}

	if (DEBUG(SUFF)) {
	    fprintf(debug_file, "not there\n");
	}

	SuffAddLevel(srcs, s);
	Lst_AtEnd(slst, s);
    }

    if (DEBUG(SUFF) && rs) {
	fprintf(debug_file, "got it\n");
    }
    return (rs);
}