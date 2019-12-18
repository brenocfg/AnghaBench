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
struct b43_wldev {int dfq_valid; } ;

/* Variables and functions */
 int B43_MACCMD_DFQ_VALID ; 
 int /*<<< orphan*/  B43_MMIO_MACCMD ; 
 int b43_read32 (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_write32 (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void handle_irq_atim_end(struct b43_wldev *dev)
{
	if (dev->dfq_valid) {
		b43_write32(dev, B43_MMIO_MACCMD,
			    b43_read32(dev, B43_MMIO_MACCMD)
			    | B43_MACCMD_DFQ_VALID);
		dev->dfq_valid = false;
	}
}