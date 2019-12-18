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
struct TYPE_2__ {int /*<<< orphan*/  ctl_addr; } ;
struct ide_hw {scalar_t__ irq; TYPE_1__ io_ports; scalar_t__* io_ports_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_H8300_IDE_ALT ; 
 scalar_t__ CONFIG_H8300_IDE_BASE ; 
 scalar_t__ CONFIG_H8300_IDE_IRQ ; 
 scalar_t__ EXT_IRQ0 ; 
 int H8300_IDE_GAP ; 
 int /*<<< orphan*/  memset (struct ide_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void hw_setup(struct ide_hw *hw)
{
	int i;

	memset(hw, 0, sizeof(*hw));
	for (i = 0; i <= 7; i++)
		hw->io_ports_array[i] = CONFIG_H8300_IDE_BASE + H8300_IDE_GAP*i;
	hw->io_ports.ctl_addr = CONFIG_H8300_IDE_ALT;
	hw->irq = EXT_IRQ0 + CONFIG_H8300_IDE_IRQ;
}