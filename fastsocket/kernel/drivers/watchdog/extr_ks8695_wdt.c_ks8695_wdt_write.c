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
 int /*<<< orphan*/  ks8695_wdt_reload () ; 

__attribute__((used)) static ssize_t ks8695_wdt_write(struct file *file, const char *data,
						size_t len, loff_t *ppos)
{
	ks8695_wdt_reload();		/* pat the watchdog */
	return len;
}