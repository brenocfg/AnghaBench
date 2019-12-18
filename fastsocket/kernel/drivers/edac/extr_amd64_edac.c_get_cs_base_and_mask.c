#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u64 ;
struct amd64_pvt {scalar_t__ ext_model; TYPE_1__* csels; } ;
struct TYPE_4__ {int x86; } ;
struct TYPE_3__ {int* csbases; int* csmasks; } ;

/* Variables and functions */
 int GENMASK (int,int) ; 
 scalar_t__ K8_REV_F ; 
 TYPE_2__ boot_cpu_data ; 

__attribute__((used)) static void get_cs_base_and_mask(struct amd64_pvt *pvt, int csrow, u8 dct,
				 u64 *base, u64 *mask)
{
	u64 csbase, csmask, base_bits, mask_bits;
	u8 addr_shift;

	if (boot_cpu_data.x86 == 0xf && pvt->ext_model < K8_REV_F) {
		csbase		= pvt->csels[dct].csbases[csrow];
		csmask		= pvt->csels[dct].csmasks[csrow];
		base_bits	= GENMASK(21, 31) | GENMASK(9, 15);
		mask_bits	= GENMASK(21, 29) | GENMASK(9, 15);
		addr_shift	= 4;

	/*
	* F16h needs two addr_shift values: 8 for high and 6 for low
	* (cf. F16h BKDG).
	*/
	} else if (boot_cpu_data.x86 == 0x16) {
		csbase          = pvt->csels[dct].csbases[csrow];
		csmask          = pvt->csels[dct].csmasks[csrow >> 1];

		*base  = (csbase & GENMASK(5,  15)) << 6;
		*base |= (csbase & GENMASK(19, 30)) << 8;

		*mask = ~0ULL;
		/* poke holes for the csmask */
		*mask &= ~((GENMASK(5, 15)  << 6) |
			   (GENMASK(19, 30) << 8));

		*mask |= (csmask & GENMASK(5, 15))  << 6;
		*mask |= (csmask & GENMASK(19, 30)) << 8;

		return;
	} else {
		csbase		= pvt->csels[dct].csbases[csrow];
		csmask		= pvt->csels[dct].csmasks[csrow >> 1];
		addr_shift	= 8;

		if (boot_cpu_data.x86 == 0x15)
			base_bits = mask_bits = GENMASK(19,30) | GENMASK(5,13);
		else
			base_bits = mask_bits = GENMASK(19,28) | GENMASK(5,13);
	}

	*base  = (csbase & base_bits) << addr_shift;

	*mask  = ~0ULL;
	/* poke holes for the csmask */
	*mask &= ~(mask_bits << addr_shift);
	/* OR them in */
	*mask |= (csmask & mask_bits) << addr_shift;
}