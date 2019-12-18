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
struct tty_struct {scalar_t__ index; TYPE_1__* driver; } ;
typedef  scalar_t__ dev_t ;
struct TYPE_2__ {int /*<<< orphan*/  minor_start; int /*<<< orphan*/  major; } ;

/* Variables and functions */
 scalar_t__ MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

dev_t tty_devnum(struct tty_struct *tty)
{
	return MKDEV(tty->driver->major, tty->driver->minor_start) + tty->index;
}