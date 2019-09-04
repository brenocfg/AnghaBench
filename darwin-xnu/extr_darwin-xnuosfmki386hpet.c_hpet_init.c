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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_2__ {int GCAP_ID; } ;
typedef  TYPE_1__ hpetReg_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,...) ; 
 int Mega ; 
 int PAGE_SIZE ; 
 int Peta ; 
 int /*<<< orphan*/  VM_WIMG_IO ; 
 int bus2hpet ; 
 int busFCvtn2t ; 
 unsigned long long busFCvtt2n ; 
 int hpet2bus ; 
 int hpet2tsc ; 
 int hpetAddr ; 
 scalar_t__ hpetArea ; 
 int hpetAreap ; 
 unsigned long long hpetCvt ; 
 int hpetCvtn2t ; 
 unsigned long long hpetCvtt2n ; 
 int hpetFemto ; 
 int hpetFreq ; 
 int hptcAE ; 
 scalar_t__ io_map_spec (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kprintf (char*,int,int,...) ; 
 int /*<<< orphan*/  map_rcbaArea () ; 
 scalar_t__ rcbaArea ; 
 int tmrCvt (unsigned long long,int) ; 
 int tsc2hpet ; 
 int tscFCvtn2t ; 
 unsigned long long tscFCvtt2n ; 

void
hpet_init(void)
{
	unsigned int	*xmod;

	map_rcbaArea();

	/*
	 * Is the HPET memory already enabled?
	 * If not, set address and enable.
	 */
	xmod = (uint32_t *)(rcbaArea + 0x3404);	/* Point to the HPTC */
	uint32_t hptc = *xmod;			/* Get HPET config */
	DBG("    current RCBA.HPTC:  %08X\n", *xmod);
	if(!(hptc & hptcAE)) {
		DBG("HPET memory is not enabled, "
		    "enabling and assigning to 0xFED00000 (hope that's ok)\n");
		*xmod = (hptc & ~3) | hptcAE;
	}

	/*
	 * Get physical address of HPET and map it.
	 */
	hpetAreap = hpetAddr | ((hptc & 3) << 12);
	hpetArea = io_map_spec(hpetAreap & -4096, PAGE_SIZE * 4, VM_WIMG_IO);
	kprintf("HPET: vaddr = %lX, paddr = %08X\n", (unsigned long)hpetArea, hpetAreap);

	/*
	 * Extract the HPET tick rate.
	 * The period of the HPET is reported in femtoseconds (10**-15s)
	 * and convert to frequency in hertz.
	 */
	hpetFemto = (uint32_t)(((hpetReg_t *)hpetArea)->GCAP_ID >> 32);
	hpetFreq = (1 * Peta) / hpetFemto;

	/*
	 * The conversion factor is the number of nanoseconds per HPET tick
	 * with about 32 bits of fraction.  The value is converted to a
	 * base-2 fixed point number.  To convert from HPET to nanoseconds,
	 * multiply the value by the conversion factor using 96-bit arithmetic,
	 * then shift right 32 bits.  If the value is known to be small,
	 * 64-bit arithmetic will work.
	 */

	/*
	 * Begin conversion of base 10 femtoseconds to base 2, calculate:
	 *  - HPET ticks to nanoseconds conversion in base 2 fraction (* 2**32)
	 *  - nanoseconds to HPET ticks conversion
	 */
	hpetCvtt2n = (uint64_t)hpetFemto << 32;
	hpetCvtt2n = hpetCvtt2n / 1000000ULL;
	hpetCvtn2t = 0xFFFFFFFFFFFFFFFFULL / hpetCvtt2n;
	kprintf("HPET: Frequency = %6d.%04dMHz, "
		"cvtt2n = %08X.%08X, cvtn2t = %08X.%08X\n",
		(uint32_t)(hpetFreq / Mega), (uint32_t)(hpetFreq % Mega), 
		(uint32_t)(hpetCvtt2n >> 32), (uint32_t)hpetCvtt2n,
		(uint32_t)(hpetCvtn2t >> 32), (uint32_t)hpetCvtn2t);


	/* (TAKE OUT LATER)
	 * Begin conversion of base 10 femtoseconds to base 2
	 * HPET ticks to nanoseconds in base 2 fraction (times 1048576)
	 */
	hpetCvt = (uint64_t)hpetFemto << 20;
	hpetCvt = hpetCvt / 1000000ULL;

	/* Calculate conversion from TSC to HPET */
	tsc2hpet = tmrCvt(tscFCvtt2n, hpetCvtn2t);
	DBG(" CVT: TSC to HPET = %08X.%08X\n",
	    (uint32_t)(tsc2hpet >> 32), (uint32_t)tsc2hpet);

	/* Calculate conversion from HPET to TSC */
	hpet2tsc = tmrCvt(hpetCvtt2n, tscFCvtn2t);
	DBG(" CVT: HPET to TSC = %08X.%08X\n",
	    (uint32_t)(hpet2tsc >> 32), (uint32_t)hpet2tsc);

	/* Calculate conversion from BUS to HPET */
	bus2hpet = tmrCvt(busFCvtt2n, hpetCvtn2t);
	DBG(" CVT: BUS to HPET = %08X.%08X\n",
	    (uint32_t)(bus2hpet >> 32), (uint32_t)bus2hpet);

	/* Calculate conversion from HPET to BUS */
	hpet2bus = tmrCvt(hpetCvtt2n, busFCvtn2t);
	DBG(" CVT: HPET to BUS = %08X.%08X\n",
	    (uint32_t)(hpet2bus >> 32), (uint32_t)hpet2bus);
}