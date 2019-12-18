#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  Hash_Entry ;
typedef  TYPE_1__ GNode ;
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FROM_DEPEND ; 
 int /*<<< orphan*/ * Hash_CreateEntry (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Hash_FindEntry (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ Hash_GetValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Hash_SetValue (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  Lst_AtEnd (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int TARG_CREATE ; 
 int TARG_NOHASH ; 
 TYPE_1__* Targ_NewGN (char const*) ; 
 int /*<<< orphan*/  VAR_GLOBAL ; 
 int /*<<< orphan*/  Var_Append (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  allTargets ; 
 scalar_t__ doing_depend ; 
 int /*<<< orphan*/  targets ; 

GNode *
Targ_FindNode(const char *name, int flags)
{
    GNode         *gn;	      /* node in that element */
    Hash_Entry	  *he = NULL; /* New or used hash entry for node */
    Boolean	  isNew;      /* Set TRUE if Hash_CreateEntry had to create */
			      /* an entry for the node */

    if (!(flags & (TARG_CREATE | TARG_NOHASH))) {
	he = Hash_FindEntry(&targets, name);
	if (he == NULL)
	    return NULL;
	return (GNode *)Hash_GetValue(he);
    }

    if (!(flags & TARG_NOHASH)) {
	he = Hash_CreateEntry(&targets, name, &isNew);
	if (!isNew)
	    return (GNode *)Hash_GetValue(he);
    }

    gn = Targ_NewGN(name);
    if (!(flags & TARG_NOHASH))
	Hash_SetValue(he, gn);
    Var_Append(".ALLTARGETS", name, VAR_GLOBAL);
    (void)Lst_AtEnd(allTargets, gn);
    if (doing_depend)
	gn->flags |= FROM_DEPEND;
    return gn;
}