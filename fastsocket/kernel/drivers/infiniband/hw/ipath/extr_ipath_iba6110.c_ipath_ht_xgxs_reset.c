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
typedef  int u64 ;
struct ipath_devdata {int ipath_control; TYPE_1__* ipath_kregs; } ;
struct TYPE_2__ {int /*<<< orphan*/  kr_control; int /*<<< orphan*/  kr_xgxsconfig; int /*<<< orphan*/  kr_scratch; } ;

/* Variables and functions */
 int INFINIPATH_C_LINKENABLE ; 
 int INFINIPATH_XGXS_RESET ; 
 int /*<<< orphan*/  ipath_read_kreg32 (struct ipath_devdata*,int /*<<< orphan*/ ) ; 
 int ipath_read_kreg64 (struct ipath_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipath_write_kreg (struct ipath_devdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ipath_ht_xgxs_reset(struct ipath_devdata *dd)
{
	u64 val, prev_val;

	prev_val = ipath_read_kreg64(dd, dd->ipath_kregs->kr_xgxsconfig);
	val = prev_val | INFINIPATH_XGXS_RESET;
	prev_val &= ~INFINIPATH_XGXS_RESET; /* be sure */
	ipath_write_kreg(dd, dd->ipath_kregs->kr_control,
			 dd->ipath_control & ~INFINIPATH_C_LINKENABLE);
	ipath_write_kreg(dd, dd->ipath_kregs->kr_xgxsconfig, val);
	ipath_read_kreg32(dd, dd->ipath_kregs->kr_scratch);
	ipath_write_kreg(dd, dd->ipath_kregs->kr_xgxsconfig, prev_val);
	ipath_write_kreg(dd, dd->ipath_kregs->kr_control,
			 dd->ipath_control);
}