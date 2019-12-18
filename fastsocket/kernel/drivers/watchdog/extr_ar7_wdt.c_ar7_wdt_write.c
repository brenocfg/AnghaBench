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
struct file {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 size_t EFAULT ; 
 int /*<<< orphan*/  ar7_wdt_kick (int) ; 
 int expect_close ; 
 scalar_t__ get_user (char,char const*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdt_lock ; 

__attribute__((used)) static ssize_t ar7_wdt_write(struct file *file, const char *data,
			     size_t len, loff_t *ppos)
{
	/* check for a magic close character */
	if (len) {
		size_t i;

		spin_lock(&wdt_lock);
		ar7_wdt_kick(1);
		spin_unlock(&wdt_lock);

		expect_close = 0;
		for (i = 0; i < len; ++i) {
			char c;
			if (get_user(c, data + i))
				return -EFAULT;
			if (c == 'V')
				expect_close = 1;
		}

	}
	return len;
}