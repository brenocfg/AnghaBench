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
struct input_dev {scalar_t__ trkid; scalar_t__ slot; scalar_t__ mtsize; int /*<<< orphan*/ * mt; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void input_mt_destroy_slots(struct input_dev *dev)
{
	kfree(dev->mt);
	dev->mt = NULL;
	dev->mtsize = 0;
	dev->slot = 0;
	dev->trkid = 0;
}