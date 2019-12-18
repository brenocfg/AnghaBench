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
typedef  int u32 ;
struct au1550_spi {TYPE_1__* regs; } ;
struct TYPE_2__ {int psc_spipcr; } ;

/* Variables and functions */
 int PSC_SPIPCR_RC ; 
 int PSC_SPIPCR_TC ; 
 int /*<<< orphan*/  au_sync () ; 

__attribute__((used)) static void au1550_spi_reset_fifos(struct au1550_spi *hw)
{
	u32 pcr;

	hw->regs->psc_spipcr = PSC_SPIPCR_RC | PSC_SPIPCR_TC;
	au_sync();
	do {
		pcr = hw->regs->psc_spipcr;
		au_sync();
	} while (pcr != 0);
}