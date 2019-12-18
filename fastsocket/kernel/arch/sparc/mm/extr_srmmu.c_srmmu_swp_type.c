#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long val; } ;
typedef  TYPE_1__ swp_entry_t ;

/* Variables and functions */
 unsigned long SRMMU_SWP_TYPE_MASK ; 
 unsigned long SRMMU_SWP_TYPE_SHIFT ; 

__attribute__((used)) static unsigned long srmmu_swp_type(swp_entry_t entry)
{
	return (entry.val >> SRMMU_SWP_TYPE_SHIFT) & SRMMU_SWP_TYPE_MASK;
}