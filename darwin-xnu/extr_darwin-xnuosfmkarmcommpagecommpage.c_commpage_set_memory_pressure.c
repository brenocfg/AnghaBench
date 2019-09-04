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
typedef  unsigned int uint32_t ;

/* Variables and functions */
 scalar_t__ _COMM_PAGE_MEMORY_PRESSURE ; 
 scalar_t__ _COMM_PAGE_RW_OFFSET ; 
 scalar_t__ commPagePtr ; 

void
commpage_set_memory_pressure(
    unsigned int    pressure )
{
	if (commPagePtr == 0)
		return;
	*((uint32_t *)(_COMM_PAGE_MEMORY_PRESSURE+_COMM_PAGE_RW_OFFSET)) = pressure;
}