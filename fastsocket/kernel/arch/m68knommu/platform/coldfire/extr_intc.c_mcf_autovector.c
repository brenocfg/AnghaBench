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
typedef  int u8 ;

/* Variables and functions */
 int EIRQ1 ; 
 int EIRQ7 ; 
 scalar_t__ MCFSIM_AVR ; 
 scalar_t__ MCF_MBAR ; 
 int __raw_readb (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writeb (int,scalar_t__) ; 

void mcf_autovector(int irq)
{
#ifdef MCFSIM_AVR
	if ((irq >= EIRQ1) && (irq <= EIRQ7)) {
		u8 avec;
		avec = __raw_readb(MCF_MBAR + MCFSIM_AVR);
		avec |= (0x1 << (irq - EIRQ1 + 1));
		__raw_writeb(avec, MCF_MBAR + MCFSIM_AVR);
	}
#endif
}