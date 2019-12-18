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
struct TYPE_2__ {int /*<<< orphan*/  users; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  at32_wdt_start () ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ *) ; 
 TYPE_1__* wdt ; 

__attribute__((used)) static int at32_wdt_open(struct inode *inode, struct file *file)
{
	if (test_and_set_bit(1, &wdt->users))
		return -EBUSY;

	at32_wdt_start();
	return nonseekable_open(inode, file);
}