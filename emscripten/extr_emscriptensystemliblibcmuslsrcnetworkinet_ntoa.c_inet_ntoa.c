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
struct in_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned char,unsigned char,unsigned char,unsigned char) ; 

char *inet_ntoa(struct in_addr in)
{
	static char buf[16];
	unsigned char *a = (void *)&in;
	snprintf(buf, sizeof buf, "%d.%d.%d.%d", a[0], a[1], a[2], a[3]);
	return buf;
}