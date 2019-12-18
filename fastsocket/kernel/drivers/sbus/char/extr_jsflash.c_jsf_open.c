#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {scalar_t__ base; int /*<<< orphan*/  busy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENXIO ; 
 TYPE_1__ jsf0 ; 
 int /*<<< orphan*/  lock_kernel () ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int jsf_open(struct inode * inode, struct file * filp)
{
	lock_kernel();
	if (jsf0.base == 0) {
		unlock_kernel();
		return -ENXIO;
	}
	if (test_and_set_bit(0, (void *)&jsf0.busy) != 0) {
		unlock_kernel();
		return -EBUSY;
	}

	unlock_kernel();
	return 0;	/* XXX What security? */
}