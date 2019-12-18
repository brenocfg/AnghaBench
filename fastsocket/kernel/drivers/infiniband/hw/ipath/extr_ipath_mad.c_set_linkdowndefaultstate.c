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
struct ipath_devdata {int /*<<< orphan*/  ipath_ibcctrl; TYPE_1__* ipath_kregs; } ;
struct TYPE_2__ {int /*<<< orphan*/  kr_ibcctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFINIPATH_IBCC_LINKDOWNDEFAULTSTATE ; 
 int /*<<< orphan*/  ipath_write_kreg (struct ipath_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_linkdowndefaultstate(struct ipath_devdata *dd, int sleep)
{
	if (sleep)
		dd->ipath_ibcctrl |= INFINIPATH_IBCC_LINKDOWNDEFAULTSTATE;
	else
		dd->ipath_ibcctrl &= ~INFINIPATH_IBCC_LINKDOWNDEFAULTSTATE;
	ipath_write_kreg(dd, dd->ipath_kregs->kr_ibcctrl,
			 dd->ipath_ibcctrl);
	return 0;
}