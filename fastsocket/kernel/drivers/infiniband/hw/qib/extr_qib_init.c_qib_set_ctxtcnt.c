#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct qib_devdata {scalar_t__ cfgctxts; scalar_t__ first_user_ctxt; scalar_t__ ctxtcnt; scalar_t__ num_pports; scalar_t__ freectxts; } ;

/* Variables and functions */
 scalar_t__ num_online_cpus () ; 
 scalar_t__ qib_cfgctxts ; 

void qib_set_ctxtcnt(struct qib_devdata *dd)
{
	if (!qib_cfgctxts) {
		dd->cfgctxts = dd->first_user_ctxt + num_online_cpus();
		if (dd->cfgctxts > dd->ctxtcnt)
			dd->cfgctxts = dd->ctxtcnt;
	} else if (qib_cfgctxts < dd->num_pports)
		dd->cfgctxts = dd->ctxtcnt;
	else if (qib_cfgctxts <= dd->ctxtcnt)
		dd->cfgctxts = qib_cfgctxts;
	else
		dd->cfgctxts = dd->ctxtcnt;
	dd->freectxts = (dd->first_user_ctxt > dd->cfgctxts) ? 0 :
		dd->cfgctxts - dd->first_user_ctxt;
}