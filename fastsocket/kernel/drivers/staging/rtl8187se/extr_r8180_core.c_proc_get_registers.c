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
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int read_nic_byte (struct net_device*,int) ; 
 scalar_t__ snprintf (char*,int,char*,...) ; 

__attribute__((used)) static int proc_get_registers(char *page, char **start,
			  off_t offset, int count,
			  int *eof, void *data)
{
	struct net_device *dev = data;
	int len = 0;
	int i,n;
	int max = 0xff;

	/* This dump the current register page */
	for (n = 0; n <= max;) {
		len += snprintf(page + len, count - len, "\nD:  %2x > ", n);

		for (i = 0; i < 16 && n <= max; i++, n++)
			len += snprintf(page + len, count - len, "%2x ",
					read_nic_byte(dev, n));
	}
	len += snprintf(page + len, count - len,"\n");

	*eof = 1;
	return len;
}