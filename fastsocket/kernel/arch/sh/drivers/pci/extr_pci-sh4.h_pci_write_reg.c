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
struct pci_channel {scalar_t__ reg_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ctrl_outl (unsigned long,scalar_t__) ; 

__attribute__((used)) static inline void pci_write_reg(struct pci_channel *chan,
				 unsigned long val, unsigned long reg)
{
	ctrl_outl(val, chan->reg_base + reg);
}