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
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ Suff ;
typedef  int /*<<< orphan*/ * LstNode ;

/* Variables and functions */
 scalar_t__ Lst_Datum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Lst_Find (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARSE_WARNING ; 
 int /*<<< orphan*/  Parse_Error (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SUFF_NULL ; 
 int /*<<< orphan*/  SuffSuffHasNameP ; 
 TYPE_1__* suffNull ; 
 int /*<<< orphan*/  sufflist ; 

void
Suff_SetNull(char *name)
{
    Suff    *s;
    LstNode ln;

    ln = Lst_Find(sufflist, name, SuffSuffHasNameP);
    if (ln != NULL) {
	s = (Suff *)Lst_Datum(ln);
	if (suffNull != NULL) {
	    suffNull->flags &= ~SUFF_NULL;
	}
	s->flags |= SUFF_NULL;
	/*
	 * XXX: Here's where the transformation mangling would take place
	 */
	suffNull = s;
    } else {
	Parse_Error(PARSE_WARNING, "Desired null suffix %s not defined.",
		     name);
    }
}