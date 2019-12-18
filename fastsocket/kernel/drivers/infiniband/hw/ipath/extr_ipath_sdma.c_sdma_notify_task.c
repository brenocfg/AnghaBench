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
struct ipath_devdata {int /*<<< orphan*/  ipath_sdma_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPATH_SDMA_SHUTDOWN ; 
 int /*<<< orphan*/  sdma_notify_taskbody (struct ipath_devdata*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sdma_notify_task(unsigned long opaque)
{
	struct ipath_devdata *dd = (struct ipath_devdata *)opaque;

	if (!test_bit(IPATH_SDMA_SHUTDOWN, &dd->ipath_sdma_status))
		sdma_notify_taskbody(dd);
}