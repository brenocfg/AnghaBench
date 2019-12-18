#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ t_type; struct TYPE_7__* t_tdesc; scalar_t__ t_id; scalar_t__ t_name; TYPE_3__* t_members; } ;
typedef  TYPE_1__ tdesc_t ;
struct TYPE_8__ {int /*<<< orphan*/  td_nextid; } ;
typedef  TYPE_2__ tdata_t ;
typedef  int /*<<< orphan*/  strs ;
struct TYPE_9__ {TYPE_1__* ml_type; scalar_t__ ml_name; struct TYPE_9__* ml_next; } ;
typedef  TYPE_3__ mlist_t ;

/* Variables and functions */
 scalar_t__ POINTER ; 
 scalar_t__ STRUCT ; 
 scalar_t__ TYPEDEF ; 
 int /*<<< orphan*/  debug (int,char*,char const*,char const*,char const*) ; 
 TYPE_1__* lookupname (char const*) ; 
 scalar_t__ streq (scalar_t__,char const*) ; 
 TYPE_1__* xcalloc (int) ; 

__attribute__((used)) static void
fix_ptrptr_to_struct(tdata_t *td)
{
	const char *strs[2] = { "as", "fdbuffer" };
	const char *mems[2] = { "a_objectdir", "fd_shadow" };
	const char *acts[2] = { "vnode", "page" };
	const char *tgts[2] = { "vnode_t", "page_t" };
	tdesc_t *str;
	tdesc_t *act, *tgt;
	tdesc_t *p1, *p2;
	mlist_t *ml;
	int i;

	for (i = 0; i < (int) (sizeof (strs) / sizeof (strs[0])); i++) {
		if (!(str = lookupname(strs[i])) || str->t_type != STRUCT)
			continue;

		for (ml = str->t_members; ml; ml = ml->ml_next) {
			if (streq(ml->ml_name, mems[i]))
				break;
		}
		if (!ml)
			continue;

		if (ml->ml_type->t_type != POINTER || ml->ml_type->t_name ||
		    ml->ml_type->t_tdesc->t_type != POINTER ||
		    ml->ml_type->t_tdesc->t_name)
			continue;

		act = ml->ml_type->t_tdesc->t_tdesc;
		if (act->t_type != STRUCT || !streq(act->t_name, acts[i]))
			continue;

		if (!(tgt = lookupname(tgts[i])) || tgt->t_type != TYPEDEF)
			continue;

		/* We have an instance of the bug */
		p2 = xcalloc(sizeof (*p2));
		p2->t_type = POINTER;
		p2->t_id = td->td_nextid++;
		p2->t_tdesc = tgt;

		p1 = xcalloc(sizeof (*p1));
		p1->t_type = POINTER;
		p1->t_id = td->td_nextid++;
		p1->t_tdesc = p2;

		ml->ml_type = p1;

		debug(3, "Fixed %s->%s => ptrptr struct %s bug\n",
		    strs[i], mems[i], acts[i]);
	}
}