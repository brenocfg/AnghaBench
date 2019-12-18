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
typedef  int s64 ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */

__attribute__((used)) static s32 scaled_ppm_to_ppb(long ppm)
{
	/*
	 * The 'freq' field in the 'struct timex' is in parts per
	 * million, but with a 16 bit binary fractional field.
	 *
	 * We want to calculate
	 *
	 *    ppb = scaled_ppm * 1000 / 2^16
	 *
	 * which simplifies to
	 *
	 *    ppb = scaled_ppm * 125 / 2^13
	 */
	s64 ppb = 1 + ppm;
	ppb *= 125;
	ppb >>= 13;
	return (s32) ppb;
}