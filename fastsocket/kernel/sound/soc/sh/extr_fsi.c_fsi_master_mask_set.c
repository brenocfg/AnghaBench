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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ MREG_END ; 
 scalar_t__ MREG_START ; 
 int __fsi_reg_mask_set (scalar_t__,scalar_t__,scalar_t__) ; 
 TYPE_1__* master ; 

__attribute__((used)) static int fsi_master_mask_set(u32 reg, u32 mask, u32 data)
{
	if ((reg < MREG_START) ||
	    (reg > MREG_END))
		return -1;

	return __fsi_reg_mask_set((u32)(master->base + reg), mask, data);
}