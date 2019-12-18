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
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,unsigned short,unsigned short) ; 

char *dn_addr2asc(__u16 addr, char *buf)
{
	unsigned short node, area;

	node = addr & 0x03ff;
	area = addr >> 10;
	sprintf(buf, "%hd.%hd", area, node);

	return buf;
}