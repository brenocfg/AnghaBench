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
typedef  int /*<<< orphan*/  sb_devc ;

/* Variables and functions */
 int sb_getmixer (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  sb_setmixer (int /*<<< orphan*/ *,unsigned int,int) ; 

void sb_chgmixer
	(sb_devc * devc, unsigned int reg, unsigned int mask, unsigned int val)
{
	int value;

	value = sb_getmixer(devc, reg);
	value = (value & ~mask) | (val & mask);
	sb_setmixer(devc, reg, value);
}