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
typedef  int u64 ;
struct ipath_devdata {int /*<<< orphan*/  ipath_sdma_abort_task; int /*<<< orphan*/  ipath_sdma_status; int /*<<< orphan*/  ipath_sdma_lock; } ;

/* Variables and functions */
 int INFINIPATH_I_SDMADISABLED ; 
 int INFINIPATH_I_SDMAINT ; 
 int /*<<< orphan*/  IPATH_SDMA_ABORTING ; 
 int /*<<< orphan*/  IPATH_SDMA_DISABLED ; 
 int /*<<< orphan*/  IPATH_SDMA_SHUTDOWN ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipath_cancel_sends (struct ipath_devdata*,int) ; 
 int /*<<< orphan*/  ipath_dbg (char*,char*) ; 
 int /*<<< orphan*/  ipath_sdma_intr (struct ipath_devdata*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_sdma_intr(struct ipath_devdata *dd, u64 istat)
{
	unsigned long flags;
	int expected;

	if ((istat & INFINIPATH_I_SDMAINT) &&
	    !test_bit(IPATH_SDMA_SHUTDOWN, &dd->ipath_sdma_status))
		ipath_sdma_intr(dd);

	if (istat & INFINIPATH_I_SDMADISABLED) {
		expected = test_bit(IPATH_SDMA_ABORTING,
			&dd->ipath_sdma_status);
		ipath_dbg("%s SDmaDisabled intr\n",
			expected ? "expected" : "unexpected");
		spin_lock_irqsave(&dd->ipath_sdma_lock, flags);
		__set_bit(IPATH_SDMA_DISABLED, &dd->ipath_sdma_status);
		spin_unlock_irqrestore(&dd->ipath_sdma_lock, flags);
		if (!expected)
			ipath_cancel_sends(dd, 1);
		if (!test_bit(IPATH_SDMA_SHUTDOWN, &dd->ipath_sdma_status))
			tasklet_hi_schedule(&dd->ipath_sdma_abort_task);
	}
}