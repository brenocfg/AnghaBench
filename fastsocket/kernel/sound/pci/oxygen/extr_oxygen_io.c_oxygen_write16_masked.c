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
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/ * _16; } ;
struct oxygen {TYPE_1__ saved_registers; scalar_t__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

void oxygen_write16_masked(struct oxygen *chip, unsigned int reg,
			   u16 value, u16 mask)
{
	u16 tmp = inw(chip->addr + reg);
	tmp &= ~mask;
	tmp |= value & mask;
	outw(tmp, chip->addr + reg);
	chip->saved_registers._16[reg / 2] = cpu_to_le16(tmp);
}