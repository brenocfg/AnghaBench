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
typedef  int u32 ;
struct stv0900_internal {int dummy; } ;
typedef  int s32 ;
typedef  enum fe_stv0900_demod_num { ____Placeholder_fe_stv0900_demod_num } fe_stv0900_demod_num ;

/* Variables and functions */
 int /*<<< orphan*/  CAR_FREQ0 ; 
 int /*<<< orphan*/  CAR_FREQ1 ; 
 int /*<<< orphan*/  CAR_FREQ2 ; 
 int ge2comp (int,int) ; 
 int stv0900_get_bits (struct stv0900_internal*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 stv0900_get_carr_freq(struct stv0900_internal *intp, u32 mclk,
					enum fe_stv0900_demod_num demod)
{
	s32	derot,
		rem1,
		rem2,
		intval1,
		intval2;

	derot = (stv0900_get_bits(intp, CAR_FREQ2) << 16) +
		(stv0900_get_bits(intp, CAR_FREQ1) << 8) +
		(stv0900_get_bits(intp, CAR_FREQ0));

	derot = ge2comp(derot, 24);
	intval1 = mclk >> 12;
	intval2 = derot >> 12;
	rem1 = mclk % 0x1000;
	rem2 = derot % 0x1000;
	derot = (intval1 * intval2) +
		((intval1 * rem2) >> 12) +
		((intval2 * rem1) >> 12);

	return derot;
}