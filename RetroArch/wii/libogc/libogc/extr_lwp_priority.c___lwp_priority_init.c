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
typedef  int u32 ;

/* Variables and functions */
 scalar_t__* _prio_bitmap ; 
 scalar_t__ _prio_major_bitmap ; 

void __lwp_priority_init()
{
	u32 index;

	_prio_major_bitmap = 0;
	for(index=0;index<16;index++)
		_prio_bitmap[index] = 0;

}