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
 int ERR ; 
 scalar_t__ addr_cnt ; 
 int addr_last ; 
 char* errmsg ; 
 int first_addr ; 
 int second_addr ; 

int
check_addr_range(long n, long m)
{
	if (addr_cnt == 0) {
		first_addr = n;
		second_addr = m;
	}
	if (first_addr > second_addr || 1 > first_addr ||
	    second_addr > addr_last) {
		errmsg = "invalid address";
		return ERR;
	}
	return 0;
}