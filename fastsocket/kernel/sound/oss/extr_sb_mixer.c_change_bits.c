#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__*** iomap; } ;
typedef  TYPE_2__ sb_devc ;
struct TYPE_4__ {int nbits; int bitoffs; } ;

/* Variables and functions */
 size_t LEFT_CHN ; 

__attribute__((used)) static void change_bits(sb_devc * devc, unsigned char *regval, int dev, int chn, int newval)
{
	unsigned char mask;
	int shift;

	mask = (1 << (*devc->iomap)[dev][chn].nbits) - 1;
	newval = (int) ((newval * mask) + 50) / 100;	/* Scale */

	shift = (*devc->iomap)[dev][chn].bitoffs - (*devc->iomap)[dev][LEFT_CHN].nbits + 1;

	*regval &= ~(mask << shift);	/* Mask out previous value */
	*regval |= (newval & mask) << shift;	/* Set the new value */
}