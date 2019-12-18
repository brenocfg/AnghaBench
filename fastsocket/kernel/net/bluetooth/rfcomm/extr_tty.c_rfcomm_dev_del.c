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
struct rfcomm_dev {int /*<<< orphan*/  list; int /*<<< orphan*/  opened; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_dev*) ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFCOMM_TTY_RELEASED ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfcomm_dev_lock ; 
 int /*<<< orphan*/  rfcomm_dev_put (struct rfcomm_dev*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rfcomm_dev_del(struct rfcomm_dev *dev)
{
	BT_DBG("dev %p", dev);

	BUG_ON(test_and_set_bit(RFCOMM_TTY_RELEASED, &dev->flags));

	if (atomic_read(&dev->opened) > 0)
		return;

	write_lock_bh(&rfcomm_dev_lock);
	list_del_init(&dev->list);
	write_unlock_bh(&rfcomm_dev_lock);

	rfcomm_dev_put(dev);
}