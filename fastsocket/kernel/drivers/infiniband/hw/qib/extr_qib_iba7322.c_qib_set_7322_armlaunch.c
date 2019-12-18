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
typedef  scalar_t__ u32 ;
struct qib_devdata {TYPE_1__* cspec; } ;
struct TYPE_2__ {int /*<<< orphan*/  errormask; } ;

/* Variables and functions */
 int /*<<< orphan*/  QIB_E_SPIOARMLAUNCH ; 
 int /*<<< orphan*/  kr_errclear ; 
 int /*<<< orphan*/  kr_errmask ; 
 int /*<<< orphan*/  qib_write_kreg (struct qib_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qib_set_7322_armlaunch(struct qib_devdata *dd, u32 enable)
{
	if (enable) {
		qib_write_kreg(dd, kr_errclear, QIB_E_SPIOARMLAUNCH);
		dd->cspec->errormask |= QIB_E_SPIOARMLAUNCH;
	} else
		dd->cspec->errormask &= ~QIB_E_SPIOARMLAUNCH;
	qib_write_kreg(dd, kr_errmask, dd->cspec->errormask);
}