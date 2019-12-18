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
struct sas_task {int dummy; } ;
struct isci_remote_device {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDEV_IO_NCQERROR ; 
 int /*<<< orphan*/  IDEV_IO_READY ; 
 scalar_t__ isci_task_is_ncq_recovery (struct sas_task*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int isci_device_io_ready(struct isci_remote_device *idev,
				       struct sas_task *task)
{
	return idev ? test_bit(IDEV_IO_READY, &idev->flags) ||
		      (test_bit(IDEV_IO_NCQERROR, &idev->flags) &&
		       isci_task_is_ncq_recovery(task))
		    : 0;
}