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
typedef  int /*<<< orphan*/  u8_t ;
typedef  scalar_t__ u64_t ;
typedef  size_t u16_t ;

/* Variables and functions */
 size_t BMLEN ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

u8_t isChanBitMaskZero(u64_t *bitmask)
{
	u16_t i;

	for (i=0; i<BMLEN; i++) {
		if (bitmask[i] != 0)
			return FALSE;
	}
	return TRUE;
}