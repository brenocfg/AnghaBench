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
 int /*<<< orphan*/  _PAGE_CACHE_WC ; 
 int _set_memory_array (unsigned long*,int,int /*<<< orphan*/ ) ; 

int set_memory_array_wc(unsigned long *addr, int addrinarray)
{
	return _set_memory_array(addr, addrinarray, _PAGE_CACHE_WC);
}