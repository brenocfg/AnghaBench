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
 unsigned long* MCCR ; 
 unsigned long MCCR_DCACHE_CBINV ; 
 unsigned long MCCR_ICACHE_INV ; 
 unsigned long MCCR_IIV ; 

void _flush_cache_all(void)
{
#if defined(CONFIG_CHIP_M32102)
	unsigned char mccr;
	*MCCR = MCCR_ICACHE_INV;
#elif defined(CONFIG_CHIP_M32104)
	unsigned short mccr;

	/* Copyback and invalidate D-cache */
	/* Invalidate I-cache */
	*MCCR |= (MCCR_ICACHE_INV | MCCR_DCACHE_CBINV);
#else
	unsigned long mccr;

	/* Copyback and invalidate D-cache */
	/* Invalidate I-cache */
	*MCCR = MCCR_ICACHE_INV | MCCR_DCACHE_CBINV;
#endif
	while ((mccr = *MCCR) & MCCR_IIV); /* loop while invalidating... */
}