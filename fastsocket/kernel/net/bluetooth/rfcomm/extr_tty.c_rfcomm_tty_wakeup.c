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
struct tty_struct {int dummy; } ;
struct rfcomm_dev {struct tty_struct* tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_dev*,struct tty_struct*) ; 
 int /*<<< orphan*/  tty_wakeup (struct tty_struct*) ; 

__attribute__((used)) static void rfcomm_tty_wakeup(unsigned long arg)
{
	struct rfcomm_dev *dev = (void *) arg;
	struct tty_struct *tty = dev->tty;
	if (!tty)
		return;

	BT_DBG("dev %p tty %p", dev, tty);
	tty_wakeup(tty);
}