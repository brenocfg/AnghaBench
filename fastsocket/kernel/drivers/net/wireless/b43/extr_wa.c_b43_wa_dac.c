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
struct TYPE_2__ {int analog; } ;
struct b43_wldev {TYPE_1__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_OFDMTAB_DAC ; 
 int b43_ofdmtab_read16 (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_ofdmtab_write16 (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void b43_wa_dac(struct b43_wldev *dev)
{
	if (dev->phy.analog == 1)
		b43_ofdmtab_write16(dev, B43_OFDMTAB_DAC, 1,
			(b43_ofdmtab_read16(dev, B43_OFDMTAB_DAC, 1) & ~0x0034) | 0x0008);
	else
		b43_ofdmtab_write16(dev, B43_OFDMTAB_DAC, 1,
			(b43_ofdmtab_read16(dev, B43_OFDMTAB_DAC, 1) & ~0x0078) | 0x0010);
}