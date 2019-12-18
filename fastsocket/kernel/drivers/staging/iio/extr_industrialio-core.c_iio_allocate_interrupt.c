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
struct iio_interrupt {int /*<<< orphan*/  ev_list; int /*<<< orphan*/  ev_list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct iio_interrupt* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct iio_interrupt *iio_allocate_interrupt(void)
{
	struct iio_interrupt *i = kmalloc(sizeof *i, GFP_KERNEL);
	if (i) {
		spin_lock_init(&i->ev_list_lock);
		INIT_LIST_HEAD(&i->ev_list);
	}
	return i;
}