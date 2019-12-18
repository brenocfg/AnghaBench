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
 scalar_t__ get_user (char,char const*) ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  sh_wdt_keepalive () ; 
 int shwdt_expect_close ; 

__attribute__((used)) static ssize_t sh_wdt_write(struct file *file, const char *buf,
			    size_t count, loff_t *ppos)
{
	if (count) {
		if (!nowayout) {
			size_t i;

			shwdt_expect_close = 0;

			for (i = 0; i != count; i++) {
				char c;
				if (get_user(c, buf + i))
					return -EFAULT;
				if (c == 'V')
					shwdt_expect_close = 42;
			}
		}
		sh_wdt_keepalive();
	}

	return count;
}