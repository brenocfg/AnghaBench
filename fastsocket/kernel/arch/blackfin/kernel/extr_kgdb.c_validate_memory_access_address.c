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
 int EFAULT ; 
 int bfin_mem_access_type (unsigned long,int) ; 

__attribute__((used)) static int validate_memory_access_address(unsigned long addr, int size)
{
	if (size < 0 || addr == 0)
		return -EFAULT;
	return bfin_mem_access_type(addr, size);
}