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

/* Variables and functions */
 int /*<<< orphan*/  iowrite8 (unsigned char,scalar_t__) ; 
 int mmio_nvram_len ; 
 int /*<<< orphan*/  mmio_nvram_lock ; 
 scalar_t__ mmio_nvram_start ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void mmio_nvram_write_val(int addr, unsigned char val)
{
	unsigned long flags;

	if (addr < mmio_nvram_len) {
		spin_lock_irqsave(&mmio_nvram_lock, flags);

		iowrite8(val, mmio_nvram_start + addr);

		spin_unlock_irqrestore(&mmio_nvram_lock, flags);
	}
}