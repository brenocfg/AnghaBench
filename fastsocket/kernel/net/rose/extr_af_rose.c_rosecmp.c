#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__* rose_addr; } ;
typedef  TYPE_1__ rose_address ;

/* Variables and functions */

int rosecmp(rose_address *addr1, rose_address *addr2)
{
	int i;

	for (i = 0; i < 5; i++)
		if (addr1->rose_addr[i] != addr2->rose_addr[i])
			return 1;

	return 0;
}