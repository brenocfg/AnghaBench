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
typedef  int u32 ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  swcrr; } ;

/* Variables and functions */
 int EBUSY ; 
 int SWCRR_SWEN ; 
 int SWCRR_SWPR ; 
 int SWCRR_SWRI ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 scalar_t__ nowayout ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ prescale ; 
 scalar_t__ reset ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int timeout ; 
 TYPE_1__* wd_base ; 
 int /*<<< orphan*/  wdt_is_open ; 
 int /*<<< orphan*/  wdt_timer ; 

__attribute__((used)) static int mpc8xxx_wdt_open(struct inode *inode, struct file *file)
{
	u32 tmp = SWCRR_SWEN;
	if (test_and_set_bit(0, &wdt_is_open))
		return -EBUSY;

	/* Once we start the watchdog we can't stop it */
	if (nowayout)
		__module_get(THIS_MODULE);

	/* Good, fire up the show */
	if (prescale)
		tmp |= SWCRR_SWPR;
	if (reset)
		tmp |= SWCRR_SWRI;

	tmp |= timeout << 16;

	out_be32(&wd_base->swcrr, tmp);

	del_timer_sync(&wdt_timer);

	return nonseekable_open(inode, file);
}