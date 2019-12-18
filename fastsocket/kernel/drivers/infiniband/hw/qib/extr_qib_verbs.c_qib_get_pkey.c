#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qib_pportdata {unsigned int hw_pidx; struct qib_devdata* dd; } ;
struct qib_ibport {int dummy; } ;
struct qib_devdata {TYPE_1__** rcd; } ;
struct TYPE_2__ {unsigned int* pkeys; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned int*) ; 
 struct qib_pportdata* ppd_from_ibp (struct qib_ibport*) ; 

unsigned qib_get_pkey(struct qib_ibport *ibp, unsigned index)
{
	struct qib_pportdata *ppd = ppd_from_ibp(ibp);
	struct qib_devdata *dd = ppd->dd;
	unsigned ctxt = ppd->hw_pidx;
	unsigned ret;

	/* dd->rcd null if mini_init or some init failures */
	if (!dd->rcd || index >= ARRAY_SIZE(dd->rcd[ctxt]->pkeys))
		ret = 0;
	else
		ret = dd->rcd[ctxt]->pkeys[index];

	return ret;
}