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
typedef  int u8 ;
typedef  int s32 ;

/* Variables and functions */
 int SHIFT ; 
 int carl9170_interpolate_s32 (int,int,int,int,int) ; 

__attribute__((used)) static u8 carl9170_interpolate_u8(u8 x, u8 x1, u8 y1, u8 x2, u8 y2)
{
#define SHIFT		8
	s32 y;

	y = carl9170_interpolate_s32(x << SHIFT, x1 << SHIFT,
		y1 << SHIFT, x2 << SHIFT, y2 << SHIFT);

	/*
	 * XXX: unwrap this expression
	 *	Isn't it just DIV_ROUND_UP(y, 1<<SHIFT)?
	 *	Can we rely on the compiler to optimise away the div?
	 */
	return (y >> SHIFT) + ((y & (1 << (SHIFT - 1))) >> (SHIFT - 1));
#undef SHIFT
}