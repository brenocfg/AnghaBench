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
struct file {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int expect_close; scalar_t__ next_heartbeat; } ;

/* Variables and functions */
 size_t EFAULT ; 
 int HZ ; 
 TYPE_1__ at91wdt_private ; 
 scalar_t__ get_user (char,char const*) ; 
 int heartbeat ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  nowayout ; 

__attribute__((used)) static ssize_t at91_wdt_write(struct file *file, const char *data, size_t len,
								loff_t *ppos)
{
	if (!len)
		return 0;

	/* Scan for magic character */
	if (!nowayout) {
		size_t i;

		at91wdt_private.expect_close = 0;

		for (i = 0; i < len; i++) {
			char c;
			if (get_user(c, data + i))
				return -EFAULT;
			if (c == 'V') {
				at91wdt_private.expect_close = 42;
				break;
			}
		}
	}

	at91wdt_private.next_heartbeat = jiffies + heartbeat * HZ;

	return len;
}