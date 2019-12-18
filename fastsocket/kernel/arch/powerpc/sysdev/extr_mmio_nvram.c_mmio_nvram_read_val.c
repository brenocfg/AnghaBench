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
 unsigned char ioread8 (scalar_t__) ; 
 int mmio_nvram_len ; 
 int /*<<< orphan*/  mmio_nvram_lock ; 
 scalar_t__ mmio_nvram_start ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned char mmio_nvram_read_val(int addr)
{
	unsigned long flags;
	unsigned char val;

	if (addr >= mmio_nvram_len)
		return 0xff;

	spin_lock_irqsave(&mmio_nvram_lock, flags);

	val = ioread8(mmio_nvram_start + addr);

	spin_unlock_irqrestore(&mmio_nvram_lock, flags);

	return val;
}