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

/* Variables and functions */
 scalar_t__ COMPARE (char const*,char*) ; 
 int atoi (char const*) ; 

__attribute__((used)) static int is_rfc1918addr(const char * addr)
{
	/* 192.168.0.0     -   192.168.255.255 (192.168/16 prefix) */
	if(COMPARE(addr, "192.168."))
		return 1;
	/* 10.0.0.0        -   10.255.255.255  (10/8 prefix) */
	if(COMPARE(addr, "10."))
		return 1;
	/* 172.16.0.0      -   172.31.255.255  (172.16/12 prefix) */
	if(COMPARE(addr, "172.")) {
		int i = atoi(addr + 4);
		if((16 <= i) && (i <= 31))
			return 1;
	}
	return 0;
}