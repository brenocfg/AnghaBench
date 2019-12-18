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
struct TYPE_2__ {scalar_t__ cap; } ;

/* Variables and functions */
 TYPE_1__ hw_bank ; 
 scalar_t__ hw_cread (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static u32 hw_ctest_and_clear(u32 addr, u32 mask)
{
	u32 reg = hw_cread(addr, mask);

	iowrite32(reg, addr + hw_bank.cap);
	return reg;
}