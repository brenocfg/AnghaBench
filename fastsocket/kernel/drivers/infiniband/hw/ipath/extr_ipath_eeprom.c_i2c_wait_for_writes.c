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
struct ipath_devdata {TYPE_1__* ipath_kregs; } ;
struct TYPE_2__ {int /*<<< orphan*/  kr_scratch; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipath_read_kreg32 (struct ipath_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmb () ; 

__attribute__((used)) static void i2c_wait_for_writes(struct ipath_devdata *dd)
{
	(void)ipath_read_kreg32(dd, dd->ipath_kregs->kr_scratch);
	rmb();
}