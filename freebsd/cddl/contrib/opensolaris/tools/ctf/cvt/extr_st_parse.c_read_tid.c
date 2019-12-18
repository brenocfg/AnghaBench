#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int t_id; struct TYPE_8__* t_tdesc; int /*<<< orphan*/  t_type; } ;
typedef  TYPE_1__ tdesc_t ;

/* Variables and functions */
 int /*<<< orphan*/  TYPEDEF ; 
 int /*<<< orphan*/  addhash (TYPE_1__*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 char* id (char*,int*) ; 
 TYPE_1__* lookup (int) ; 
 char* tdefdecl (char*,int,TYPE_1__**) ; 
 TYPE_1__* unres_new (int) ; 
 TYPE_1__* xcalloc (int) ; 

__attribute__((used)) static char *
read_tid(char *cp, tdesc_t **tdpp)
{
	tdesc_t *tdp;
	int tid;

	cp = id(cp, &tid);

	assert(tid != 0);

	if (*cp == '=') {
		if (!(cp = tdefdecl(cp + 1, tid, &tdp)))
			return (NULL);
		if (tdp->t_id && tdp->t_id != tid) {
			tdesc_t *ntdp = xcalloc(sizeof (*ntdp));

			ntdp->t_type = TYPEDEF;
			ntdp->t_tdesc = tdp;
			tdp = ntdp;
		}
		addhash(tdp, tid);
	} else if ((tdp = lookup(tid)) == NULL)
		tdp = unres_new(tid);

	*tdpp = tdp;
	return (cp);
}