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
typedef  scalar_t__ u64 ;
struct ipath_devdata {TYPE_1__* ipath_kregs; } ;
struct TYPE_2__ {int /*<<< orphan*/  kr_serdesconfig0; } ;

/* Variables and functions */
 scalar_t__ INFINIPATH_SERDC0_TXIDLE ; 
 int /*<<< orphan*/  ipath_dbg (char*,unsigned long long) ; 
 scalar_t__ ipath_read_kreg64 (struct ipath_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipath_write_kreg (struct ipath_devdata*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ipath_ht_quiet_serdes(struct ipath_devdata *dd)
{
	u64 val = ipath_read_kreg64(dd, dd->ipath_kregs->kr_serdesconfig0);

	val |= INFINIPATH_SERDC0_TXIDLE;
	ipath_dbg("Setting TxIdleEn on serdes (config0 = %llx)\n",
		  (unsigned long long) val);
	ipath_write_kreg(dd, dd->ipath_kregs->kr_serdesconfig0, val);
}