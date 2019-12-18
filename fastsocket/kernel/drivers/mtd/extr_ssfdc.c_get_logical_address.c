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
typedef  int uint8_t ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  MTD_DEBUG_LEVEL0 ; 
 int /*<<< orphan*/  MTD_DEBUG_LEVEL3 ; 
 int get_parity (int,int) ; 

__attribute__((used)) static int get_logical_address(uint8_t *oob_buf)
{
	int block_address, parity;
	int offset[2] = {6, 11}; /* offset of the 2 address fields within OOB */
	int j;
	int ok = 0;

	/*
	 * Look for the first valid logical address
	 * Valid address has fixed pattern on most significant bits and
	 * parity check
	 */
	for (j = 0; j < ARRAY_SIZE(offset); j++) {
		block_address = ((int)oob_buf[offset[j]] << 8) |
			oob_buf[offset[j]+1];

		/* Check for the signature bits in the address field (MSBits) */
		if ((block_address & ~0x7FF) == 0x1000) {
			parity = block_address & 0x01;
			block_address &= 0x7FF;
			block_address >>= 1;

			if (get_parity(block_address, 10) != parity) {
				DEBUG(MTD_DEBUG_LEVEL0,
					"SSFDC_RO: logical address field%d"
					"parity error(0x%04X)\n", j+1,
					block_address);
			} else {
				ok = 1;
				break;
			}
		}
	}

	if (!ok)
		block_address = -2;

	DEBUG(MTD_DEBUG_LEVEL3, "SSFDC_RO: get_logical_address() %d\n",
		block_address);

	return block_address;
}