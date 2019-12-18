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
struct lguest {unsigned long pfn_limit; } ;

/* Variables and functions */
 unsigned long PAGE_SIZE ; 

bool lguest_address_ok(const struct lguest *lg,
		       unsigned long addr, unsigned long len)
{
	return (addr+len) / PAGE_SIZE < lg->pfn_limit && (addr+len >= addr);
}