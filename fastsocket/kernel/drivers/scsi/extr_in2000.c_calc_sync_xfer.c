#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uchar ;
struct TYPE_2__ {unsigned int reg_value; } ;

/* Variables and functions */
 unsigned int OPTIMUM_SX_OFF ; 
 size_t round_period (unsigned int) ; 
 TYPE_1__* sx_table ; 

__attribute__((used)) static uchar calc_sync_xfer(unsigned int period, unsigned int offset)
{
	uchar result;

	period *= 4;		/* convert SDTR code to ns */
	result = sx_table[round_period(period)].reg_value;
	result |= (offset < OPTIMUM_SX_OFF) ? offset : OPTIMUM_SX_OFF;
	return result;
}