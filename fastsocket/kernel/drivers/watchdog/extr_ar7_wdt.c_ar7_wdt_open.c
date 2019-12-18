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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  ar7_wdt_enable_wdt () ; 
 scalar_t__ expect_close ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdt_is_open ; 

__attribute__((used)) static int ar7_wdt_open(struct inode *inode, struct file *file)
{
	/* only allow one at a time */
	if (test_and_set_bit(0, &wdt_is_open))
		return -EBUSY;
	ar7_wdt_enable_wdt();
	expect_close = 0;

	return nonseekable_open(inode, file);
}