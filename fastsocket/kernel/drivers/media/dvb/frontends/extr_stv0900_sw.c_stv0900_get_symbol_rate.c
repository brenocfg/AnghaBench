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
 int /*<<< orphan*/  SYMB_FREQ0 ; 
 int /*<<< orphan*/  SYMB_FREQ1 ; 
 int /*<<< orphan*/  SYMB_FREQ2 ; 
 int /*<<< orphan*/  SYMB_FREQ3 ; 
 int /*<<< orphan*/  dprintk (char*,int,int,int,int,int) ; 
 int stv0900_get_bits (struct stv0900_internal*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 stv0900_get_symbol_rate(struct stv0900_internal *intp,
					u32 mclk,
					enum fe_stv0900_demod_num demod)
{
	s32	rem1, rem2, intval1, intval2, srate;

	srate = (stv0900_get_bits(intp, SYMB_FREQ3) << 24) +
		(stv0900_get_bits(intp, SYMB_FREQ2) << 16) +
		(stv0900_get_bits(intp, SYMB_FREQ1) << 8) +
		(stv0900_get_bits(intp, SYMB_FREQ0));
	dprintk("lock: srate=%d r0=0x%x r1=0x%x r2=0x%x r3=0x%x \n",
		srate, stv0900_get_bits(intp, SYMB_FREQ0),
		stv0900_get_bits(intp, SYMB_FREQ1),
		stv0900_get_bits(intp, SYMB_FREQ2),
		stv0900_get_bits(intp, SYMB_FREQ3));

	intval1 = (mclk) >> 16;
	intval2 = (srate) >> 16;

	rem1 = (mclk) % 0x10000;
	rem2 = (srate) % 0x10000;
	srate =	(intval1 * intval2) +
		((intval1 * rem2) >> 16) +
		((intval2 * rem1) >> 16);

	return srate;
}