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
typedef  int /*<<< orphan*/  u32 ;
struct e1000_hw {unsigned long io_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  e1000_io_write (struct e1000_hw*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e1000_write_reg_io(struct e1000_hw *hw, u32 offset, u32 value)
{
	unsigned long io_addr = hw->io_base;
	unsigned long io_data = hw->io_base + 4;

	e1000_io_write(hw, io_addr, offset);
	e1000_io_write(hw, io_data, value);
}