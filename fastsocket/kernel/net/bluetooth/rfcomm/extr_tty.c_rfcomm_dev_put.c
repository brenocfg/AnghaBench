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
struct rfcomm_dev {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfcomm_dev_destruct (struct rfcomm_dev*) ; 

__attribute__((used)) static inline void rfcomm_dev_put(struct rfcomm_dev *dev)
{
	/* The reason this isn't actually a race, as you no
	   doubt have a little voice screaming at you in your
	   head, is that the refcount should never actually
	   reach zero unless the device has already been taken
	   off the list, in rfcomm_dev_del(). And if that's not
	   true, we'll hit the BUG() in rfcomm_dev_destruct()
	   anyway. */
	if (atomic_dec_and_test(&dev->refcnt))
		rfcomm_dev_destruct(dev);
}