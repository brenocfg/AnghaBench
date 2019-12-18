#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int t_id; scalar_t__ t_type; struct TYPE_8__* t_tdesc; void* t_name; } ;
typedef  TYPE_1__ tdesc_t ;
typedef  int iitype_t ;
struct TYPE_9__ {int ii_type; TYPE_1__* ii_dtype; int /*<<< orphan*/  ii_name; } ;
typedef  TYPE_2__ iidesc_t ;

/* Variables and functions */
 scalar_t__ FORWARD ; 
 int II_TYPE ; 
 scalar_t__ INTRINSIC ; 
 scalar_t__ TYPEDEF ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  expected (char*,char*,char*) ; 
 int /*<<< orphan*/  faketypenumber ; 
 char* id (char*,int*) ; 
 TYPE_1__* lookup (int) ; 
 int /*<<< orphan*/  streq (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ tagadd (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  tdefdecl (char*,int,TYPE_1__**) ; 
 TYPE_1__* xcalloc (int) ; 
 void* xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static iitype_t
parse_type(char *cp, iidesc_t *ii)
{
	tdesc_t *tdp, *ntdp;
	int tid;

	if (*cp++ != 't')
		expected("parse_type", "t (type)", cp - 1);

	cp = id(cp, &tid);
	if ((tdp = lookup(tid)) == NULL) {
		if (*cp++ != '=')
			expected("parse_type", "= (definition)", cp - 1);

		(void) tdefdecl(cp, tid, &tdp);

		if (tdp->t_id == tid) {
			assert(tdp->t_type != TYPEDEF);
			assert(!lookup(tdp->t_id));

			if (!streq(tdp->t_name, ii->ii_name)) {
				ntdp = xcalloc(sizeof (*ntdp));
				ntdp->t_name = xstrdup(ii->ii_name);
				ntdp->t_type = TYPEDEF;
				ntdp->t_tdesc = tdp;
				tdp->t_id = faketypenumber++;
				tdp = ntdp;
			}
		} else if (tdp->t_id == 0) {
			assert(tdp->t_type == FORWARD ||
			    tdp->t_type == INTRINSIC);

			if (tdp->t_name && !streq(tdp->t_name, ii->ii_name)) {
				ntdp = xcalloc(sizeof (*ntdp));
				ntdp->t_name = xstrdup(ii->ii_name);
				ntdp->t_type = TYPEDEF;
				ntdp->t_tdesc = tdp;
				tdp->t_id = faketypenumber++;
				tdp = ntdp;
			}
		} else if (tdp->t_id != tid) {
			ntdp = xcalloc(sizeof (*ntdp));
			ntdp->t_name = xstrdup(ii->ii_name);
			ntdp->t_type = TYPEDEF;
			ntdp->t_tdesc = tdp;
			tdp = ntdp;
		}

		if (tagadd(ii->ii_name, tid, tdp) < 0)
			return (-1);
	}

	ii->ii_type = II_TYPE;
	ii->ii_dtype = tdp;
	return (II_TYPE);
}