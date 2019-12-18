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
struct TYPE_2__ {int /*<<< orphan*/  timer; scalar_t__ next_heartbeat; int /*<<< orphan*/  open; } ;

/* Variables and functions */
 int EBUSY ; 
 int HZ ; 
 scalar_t__ WDT_TIMEOUT ; 
 TYPE_1__ at91wdt_private ; 
 int heartbeat ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int at91_wdt_open(struct inode *inode, struct file *file)
{
	if (test_and_set_bit(0, &at91wdt_private.open))
		return -EBUSY;

	at91wdt_private.next_heartbeat = jiffies + heartbeat * HZ;
	mod_timer(&at91wdt_private.timer, jiffies + WDT_TIMEOUT);

	return nonseekable_open(inode, file);
}