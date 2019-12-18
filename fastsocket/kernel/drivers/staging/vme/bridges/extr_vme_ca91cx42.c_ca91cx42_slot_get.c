#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ base; } ;

/* Variables and functions */
 int CA91CX42_VCSR_BS_SLOT_M ; 
 scalar_t__ VCSR_BS ; 
 TYPE_1__* ca91cx42_bridge ; 
 int ioread32 (scalar_t__) ; 

int ca91cx42_slot_get(void)
{
	u32 slot = 0;

	slot = ioread32(ca91cx42_bridge->base + VCSR_BS);
	slot = ((slot & CA91CX42_VCSR_BS_SLOT_M) >> 27);
	return (int)slot;

}