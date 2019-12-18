#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ sNum; char* name; struct TYPE_12__* ref; int /*<<< orphan*/  refCount; } ;
typedef  TYPE_1__ Suff ;
typedef  int /*<<< orphan*/ * LstNode ;
typedef  TYPE_1__* Lst ;

/* Variables and functions */
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 scalar_t__ FAILURE ; 
 int /*<<< orphan*/  Lst_AtEnd (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  Lst_Close (TYPE_1__*) ; 
 scalar_t__ Lst_Datum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lst_InsertBefore (TYPE_1__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * Lst_Next (TYPE_1__*) ; 
 scalar_t__ Lst_Open (TYPE_1__*) ; 
 int /*<<< orphan*/  SUFF ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
SuffInsert(Lst l, Suff *s)
{
    LstNode 	  ln;		/* current element in l we're examining */
    Suff          *s2 = NULL;	/* the suffix descriptor in this element */

    if (Lst_Open(l) == FAILURE) {
	return;
    }
    while ((ln = Lst_Next(l)) != NULL) {
	s2 = (Suff *)Lst_Datum(ln);
	if (s2->sNum >= s->sNum) {
	    break;
	}
    }

    Lst_Close(l);
    if (DEBUG(SUFF)) {
	fprintf(debug_file, "inserting %s(%d)...", s->name, s->sNum);
    }
    if (ln == NULL) {
	if (DEBUG(SUFF)) {
	    fprintf(debug_file, "at end of list\n");
	}
	(void)Lst_AtEnd(l, s);
	s->refCount++;
	(void)Lst_AtEnd(s->ref, l);
    } else if (s2->sNum != s->sNum) {
	if (DEBUG(SUFF)) {
	    fprintf(debug_file, "before %s(%d)\n", s2->name, s2->sNum);
	}
	(void)Lst_InsertBefore(l, ln, s);
	s->refCount++;
	(void)Lst_AtEnd(s->ref, l);
    } else if (DEBUG(SUFF)) {
	fprintf(debug_file, "already there\n");
    }
}