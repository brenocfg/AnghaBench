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
struct TYPE_2__ {scalar_t__ expect_close; int /*<<< orphan*/  timer; int /*<<< orphan*/  open; } ;

/* Variables and functions */
 TYPE_1__ at91wdt_private ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int at91_wdt_close(struct inode *inode, struct file *file)
{
	clear_bit(0, &at91wdt_private.open);

	/* stop internal ping */
	if (!at91wdt_private.expect_close)
		del_timer(&at91wdt_private.timer);

	at91wdt_private.expect_close = 0;
	return 0;
}