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
struct TYPE_4__ {size_t dt_maxagg; int /*<<< orphan*/ ** dt_aggdesc; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
typedef  size_t dtrace_aggid_t ;
typedef  int /*<<< orphan*/  dtrace_aggdesc_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int dt_aggid_add (TYPE_1__*,size_t) ; 

int
dt_aggid_lookup(dtrace_hdl_t *dtp, dtrace_aggid_t aggid,
    dtrace_aggdesc_t **adp)
{
	int rval;

	if (aggid >= dtp->dt_maxagg || dtp->dt_aggdesc[aggid] == NULL) {
		if ((rval = dt_aggid_add(dtp, aggid)) != 0)
			return (rval);
	}

	assert(aggid < dtp->dt_maxagg);
	assert(dtp->dt_aggdesc[aggid] != NULL);
	*adp = dtp->dt_aggdesc[aggid];

	return (0);
}