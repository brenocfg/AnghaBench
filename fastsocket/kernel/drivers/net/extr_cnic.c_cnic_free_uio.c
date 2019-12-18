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
struct cnic_uio_dev {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cnic_free_uio (struct cnic_uio_dev*) ; 
 int /*<<< orphan*/  cnic_dev_lock ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cnic_free_uio(struct cnic_uio_dev *udev)
{
	if (!udev)
		return;

	write_lock(&cnic_dev_lock);
	list_del_init(&udev->list);
	write_unlock(&cnic_dev_lock);
	__cnic_free_uio(udev);
}