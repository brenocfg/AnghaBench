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
typedef  int u64_t ;
typedef  int u32_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

u8_t IS_BIT_SET(u32_t bit, u64_t *bitmask)
{
	u32_t byteOffset, bitnum;
	u64_t val;

	byteOffset = bit/64;
	bitnum = bit - byteOffset*64;
	val = ((u64_t) 1) << bitnum;
	if (bitmask[byteOffset] & val)
		return TRUE;
	else
		return FALSE;
}