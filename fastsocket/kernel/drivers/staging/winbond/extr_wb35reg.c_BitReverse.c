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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ ClearBit (scalar_t__,scalar_t__) ; 
 scalar_t__ GetBit (scalar_t__,scalar_t__) ; 
 scalar_t__ SetBit (scalar_t__,scalar_t__) ; 

u32 BitReverse( u32 dwData, u32 DataLength)
{
	u32   HalfLength, i, j;
	u32   BitA, BitB;

	if ( DataLength <= 0)       return 0;   // No conversion is done.
	dwData = dwData & (0xffffffff >> (32 - DataLength));

	HalfLength = DataLength / 2;
	for ( i = 0, j = DataLength-1 ; i < HalfLength; i++, j--)
	{
		BitA = GetBit( dwData, i);
		BitB = GetBit( dwData, j);
		if (BitA && !BitB) {
			dwData = ClearBit( dwData, i);
			dwData = SetBit( dwData, j);
		} else if (!BitA && BitB) {
			dwData = SetBit( dwData, i);
			dwData = ClearBit( dwData, j);
		} else
		{
			// Do nothing since these two bits are of the save values.
		}
	}

	return dwData;
}