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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 size_t _format_mac_addr (char*,scalar_t__,unsigned char const*,int) ; 
 scalar_t__ strlcpy (char*,char*,scalar_t__) ; 

ssize_t sysfs_format_mac(char *buf, const unsigned char *addr, int len)
{
	size_t l;

	l = _format_mac_addr(buf, PAGE_SIZE, addr, len);
	l += strlcpy(buf + l, "\n", PAGE_SIZE - l);
	return ((ssize_t) l);
}