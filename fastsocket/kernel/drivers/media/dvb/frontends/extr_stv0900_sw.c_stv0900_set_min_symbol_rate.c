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
typedef  enum fe_stv0900_demod_num { ____Placeholder_fe_stv0900_demod_num } fe_stv0900_demod_num ;

/* Variables and functions */
 scalar_t__ SFRLOW1 ; 
 int /*<<< orphan*/  stv0900_write_reg (struct stv0900_internal*,scalar_t__,int) ; 

__attribute__((used)) static void stv0900_set_min_symbol_rate(struct stv0900_internal *intp,
					u32 mclk, u32 srate,
					enum fe_stv0900_demod_num demod)
{
	u32	symb;

	srate = 95 * (srate / 100);
	if (srate > 60000000) {
		symb = srate << 4;
		symb /= (mclk >> 12);

	} else if (srate > 6000000) {
		symb = srate << 6;
		symb /= (mclk >> 10);

	} else {
		symb = srate << 9;
		symb /= (mclk >> 7);
	}

	stv0900_write_reg(intp, SFRLOW1, (symb >> 8) & 0xff);
	stv0900_write_reg(intp, SFRLOW1 + 1, (symb & 0xff));
}