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
struct ipath_devdata {int /*<<< orphan*/  verbs_timer; int /*<<< orphan*/  verbs_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipath_ib_timer (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void __verbs_timer(unsigned long arg)
{
	struct ipath_devdata *dd = (struct ipath_devdata *) arg;

	/* Handle verbs layer timeouts. */
	ipath_ib_timer(dd->verbs_dev);

	mod_timer(&dd->verbs_timer, jiffies + 1);
}