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
struct hw {int dummy; } ;

/* Variables and functions */
 int hw_read_pci (struct hw*,int) ; 
 int /*<<< orphan*/  hw_write_pci (struct hw*,int,int) ; 

__attribute__((used)) static void i2c_lock(struct hw *hw)
{
	if ((hw_read_pci(hw, 0xcc) & 0xff) == 0xaa)
		hw_write_pci(hw, 0xcc, 0x00);
}