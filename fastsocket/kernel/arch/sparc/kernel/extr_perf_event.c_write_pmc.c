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
typedef  int u64 ;

/* Variables and functions */
 int PIC_UPPER_INDEX ; 
 int /*<<< orphan*/  read_pic (int) ; 
 int /*<<< orphan*/  write_pic (int) ; 

__attribute__((used)) static void write_pmc(int idx, u64 val)
{
	u64 shift, mask, pic;

	shift = 0;
	if (idx == PIC_UPPER_INDEX)
		shift = 32;

	mask = ((u64) 0xffffffff) << shift;
	val <<= shift;

	read_pic(pic);
	pic &= ~mask;
	pic |= val;
	write_pic(pic);
}