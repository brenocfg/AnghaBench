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
struct TYPE_2__ {unsigned long daemon_sleep; } ;
struct mddev {TYPE_1__ bitmap_info; } ;
typedef  int ssize_t ;

/* Variables and functions */
 unsigned long HZ ; 
 int jiffies_to_msecs (unsigned long) ; 
 int sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t
timeout_show(struct mddev *mddev, char *page)
{
	ssize_t len;
	unsigned long secs = mddev->bitmap_info.daemon_sleep / HZ;
	unsigned long jifs = mddev->bitmap_info.daemon_sleep % HZ;

	len = sprintf(page, "%lu", secs);
	if (jifs)
		len += sprintf(page+len, ".%03u", jiffies_to_msecs(jifs));
	len += sprintf(page+len, "\n");
	return len;
}