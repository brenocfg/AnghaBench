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
struct TYPE_2__ {int abs; } ;

/* Variables and functions */
 int hw_aread (int,int) ; 
 TYPE_1__ hw_bank ; 
 int /*<<< orphan*/  iowrite32 (int,int) ; 

__attribute__((used)) static void hw_awrite(u32 addr, u32 mask, u32 data)
{
	iowrite32(hw_aread(addr, ~mask) | (data & mask),
		  addr + hw_bank.abs);
}