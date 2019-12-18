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
struct wm8350 {int dummy; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 struct wm8350* get_wm8350 () ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wm8350_wdt_start (struct wm8350*) ; 
 int /*<<< orphan*/  wm8350_wdt_users ; 

__attribute__((used)) static int wm8350_wdt_open(struct inode *inode, struct file *file)
{
	struct wm8350 *wm8350 = get_wm8350();
	int ret;

	if (!wm8350)
		return -ENODEV;

	if (test_and_set_bit(0, &wm8350_wdt_users))
		return -EBUSY;

	ret = wm8350_wdt_start(wm8350);
	if (ret != 0)
		return ret;

	return nonseekable_open(inode, file);
}