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
struct rfcomm_dev {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  RFCOMM_TTY_RELEASED ; 
 struct rfcomm_dev* __rfcomm_dev_get (int) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfcomm_dev_hold (struct rfcomm_dev*) ; 
 int /*<<< orphan*/  rfcomm_dev_lock ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct rfcomm_dev *rfcomm_dev_get(int id)
{
	struct rfcomm_dev *dev;

	read_lock(&rfcomm_dev_lock);

	dev = __rfcomm_dev_get(id);

	if (dev) {
		if (test_bit(RFCOMM_TTY_RELEASED, &dev->flags))
			dev = NULL;
		else
			rfcomm_dev_hold(dev);
	}

	read_unlock(&rfcomm_dev_lock);

	return dev;
}