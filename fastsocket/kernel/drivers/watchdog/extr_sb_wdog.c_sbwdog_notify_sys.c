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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
 unsigned long SYS_DOWN ; 
 unsigned long SYS_HALT ; 
 int /*<<< orphan*/  __raw_writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kern_dog ; 
 int /*<<< orphan*/  user_dog ; 

__attribute__((used)) static int sbwdog_notify_sys(struct notifier_block *this, unsigned long code,
								void *erf)
{
	if (code == SYS_DOWN || code == SYS_HALT) {
		/*
		 * sit and sit
		 */
		__raw_writeb(0, user_dog);
		__raw_writeb(0, kern_dog);
	}

	return NOTIFY_DONE;
}