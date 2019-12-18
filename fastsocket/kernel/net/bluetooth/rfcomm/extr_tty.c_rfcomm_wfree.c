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
struct sk_buff {int /*<<< orphan*/  truesize; scalar_t__ sk; } ;
struct rfcomm_dev {int /*<<< orphan*/  wakeup_task; int /*<<< orphan*/  flags; int /*<<< orphan*/  wmem_alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  RFCOMM_TTY_ATTACHED ; 
 int /*<<< orphan*/  atomic_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfcomm_dev_put (struct rfcomm_dev*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rfcomm_wfree(struct sk_buff *skb)
{
	struct rfcomm_dev *dev = (void *) skb->sk;
	atomic_sub(skb->truesize, &dev->wmem_alloc);
	if (test_bit(RFCOMM_TTY_ATTACHED, &dev->flags))
		tasklet_schedule(&dev->wakeup_task);
	rfcomm_dev_put(dev);
}