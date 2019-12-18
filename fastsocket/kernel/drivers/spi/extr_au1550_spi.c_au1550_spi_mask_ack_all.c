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
struct au1550_spi {TYPE_1__* regs; } ;
struct TYPE_2__ {int psc_spimsk; int psc_spievent; } ;

/* Variables and functions */
 int PSC_SPIEVNT_MD ; 
 int PSC_SPIEVNT_MM ; 
 int PSC_SPIEVNT_RO ; 
 int PSC_SPIEVNT_RR ; 
 int PSC_SPIEVNT_RU ; 
 int PSC_SPIEVNT_SD ; 
 int PSC_SPIEVNT_TO ; 
 int PSC_SPIEVNT_TR ; 
 int PSC_SPIEVNT_TU ; 
 int PSC_SPIMSK_MD ; 
 int PSC_SPIMSK_MM ; 
 int PSC_SPIMSK_RO ; 
 int PSC_SPIMSK_RR ; 
 int PSC_SPIMSK_RU ; 
 int PSC_SPIMSK_SD ; 
 int PSC_SPIMSK_TO ; 
 int PSC_SPIMSK_TR ; 
 int PSC_SPIMSK_TU ; 
 int /*<<< orphan*/  au_sync () ; 

__attribute__((used)) static inline void au1550_spi_mask_ack_all(struct au1550_spi *hw)
{
	hw->regs->psc_spimsk =
		  PSC_SPIMSK_MM | PSC_SPIMSK_RR | PSC_SPIMSK_RO
		| PSC_SPIMSK_RU | PSC_SPIMSK_TR | PSC_SPIMSK_TO
		| PSC_SPIMSK_TU | PSC_SPIMSK_SD | PSC_SPIMSK_MD;
	au_sync();

	hw->regs->psc_spievent =
		  PSC_SPIEVNT_MM | PSC_SPIEVNT_RR | PSC_SPIEVNT_RO
		| PSC_SPIEVNT_RU | PSC_SPIEVNT_TR | PSC_SPIEVNT_TO
		| PSC_SPIEVNT_TU | PSC_SPIEVNT_SD | PSC_SPIEVNT_MD;
	au_sync();
}