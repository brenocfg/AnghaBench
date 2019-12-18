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
typedef  int u16 ;

/* Variables and functions */
 long TEMP_FROM_REG (int) ; 
 int* tempLUT ; 

__attribute__((used)) static inline long TEMP_FROM_REG10(u16 val)
{
	u16 eightBits = val >> 2;
	u16 twoBits = val & 3;

	/* no interpolation for these */
	if (twoBits == 0 || eightBits == 255)
		return TEMP_FROM_REG(eightBits);

	/* do some linear interpolation */
	return (tempLUT[eightBits] * (4 - twoBits) +
		tempLUT[eightBits + 1] * twoBits) * 25;
}