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
typedef  int u16 ;
struct w83627ehf_data {scalar_t__ addr; } ;

/* Variables and functions */
 scalar_t__ ADDR_REG_OFFSET ; 
 scalar_t__ DATA_REG_OFFSET ; 
 int /*<<< orphan*/  W83627EHF_REG_BANK ; 
 int /*<<< orphan*/  outb_p (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void w83627ehf_reset_bank(struct w83627ehf_data *data, u16 reg)
{
	if (reg & 0xff00) {
		outb_p(W83627EHF_REG_BANK, data->addr + ADDR_REG_OFFSET);
		outb_p(0, data->addr + DATA_REG_OFFSET);
	}
}