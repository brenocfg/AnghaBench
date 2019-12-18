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
 unsigned int INVALID_CHIP_ADDRESS ; 
 unsigned int UC_OFF (unsigned int) ; 
 scalar_t__ UC_RANGE (unsigned int,int) ; 
 unsigned int X_OFF (unsigned int) ; 
 scalar_t__ X_RANGE_ALL (unsigned int,int) ; 
 unsigned int Y_OFF (unsigned int) ; 
 scalar_t__ Y_RANGE_ALL (unsigned int,int) ; 

__attribute__((used)) static unsigned int dsp_chip_to_dsp_addx(unsigned int chip_addx,
					bool *code, bool *yram)
{
	*code = *yram = false;

	if (UC_RANGE(chip_addx, 1)) {
		*code = true;
		return UC_OFF(chip_addx);
	} else if (X_RANGE_ALL(chip_addx, 1)) {
		return X_OFF(chip_addx);
	} else if (Y_RANGE_ALL(chip_addx, 1)) {
		*yram = true;
		return Y_OFF(chip_addx);
	}

	return INVALID_CHIP_ADDRESS;
}