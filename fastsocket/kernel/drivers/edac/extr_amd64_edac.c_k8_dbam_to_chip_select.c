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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct amd64_pvt {int dclr1; int dclr0; scalar_t__ ext_model; } ;

/* Variables and functions */
 scalar_t__ K8_REV_D ; 
 scalar_t__ K8_REV_F ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int WIDTH_128 ; 
 int ddr2_cs_size (unsigned int,int) ; 

__attribute__((used)) static int k8_dbam_to_chip_select(struct amd64_pvt *pvt, u8 dct,
				  unsigned cs_mode)
{
	u32 dclr = dct ? pvt->dclr1 : pvt->dclr0;

	if (pvt->ext_model >= K8_REV_F) {
		WARN_ON(cs_mode > 11);
		return ddr2_cs_size(cs_mode, dclr & WIDTH_128);
	}
	else if (pvt->ext_model >= K8_REV_D) {
		unsigned diff;
		WARN_ON(cs_mode > 10);

		/*
		 * the below calculation, besides trying to win an obfuscated C
		 * contest, maps cs_mode values to DIMM chip select sizes. The
		 * mappings are:
		 *
		 * cs_mode	CS size (mb)
		 * =======	============
		 * 0		32
		 * 1		64
		 * 2		128
		 * 3		128
		 * 4		256
		 * 5		512
		 * 6		256
		 * 7		512
		 * 8		1024
		 * 9		1024
		 * 10		2048
		 *
		 * Basically, it calculates a value with which to shift the
		 * smallest CS size of 32MB.
		 *
		 * ddr[23]_cs_size have a similar purpose.
		 */
		diff = cs_mode/3 + (unsigned)(cs_mode > 5);

		return 32 << (cs_mode - diff);
	}
	else {
		WARN_ON(cs_mode > 6);
		return 32 << cs_mode;
	}
}