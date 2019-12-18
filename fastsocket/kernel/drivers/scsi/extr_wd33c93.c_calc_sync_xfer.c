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
typedef  unsigned int uchar ;
struct sx_period {unsigned int reg_value; } ;

/* Variables and functions */
 unsigned int OPTIMUM_SX_OFF ; 
 unsigned int STR_FSS ; 
 size_t round_period (unsigned int,struct sx_period const*) ; 

__attribute__((used)) static uchar
calc_sync_xfer(unsigned int period, unsigned int offset, unsigned int fast,
               const struct sx_period *sx_table)
{
	/* When doing Fast SCSI synchronous data transfers, the corresponding
	 * value in 'sx_table' is two times the actually used transfer period.
	 */
	uchar result;

	if (offset && fast) {
		fast = STR_FSS;
		period *= 2;
	} else {
		fast = 0;
	}
	period *= 4;		/* convert SDTR code to ns */
	result = sx_table[round_period(period,sx_table)].reg_value;
	result |= (offset < OPTIMUM_SX_OFF) ? offset : OPTIMUM_SX_OFF;
	result |= fast;
	return result;
}