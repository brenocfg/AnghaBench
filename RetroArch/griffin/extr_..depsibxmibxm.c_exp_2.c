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

/* Variables and functions */
 int FP_MASK ; 
 int FP_SHIFT ; 
 int* exp2_table ; 

__attribute__((used)) static int exp_2( int x ) {
	int c, m, y;
	int x0 = ( x & FP_MASK ) >> ( FP_SHIFT - 7 );
	c = exp2_table[ x0 ];
	m = exp2_table[ x0 + 1 ] - c;
	y = ( m * ( x & ( FP_MASK >> 7 ) ) >> 8 ) + c;
	return ( y << FP_SHIFT ) >> ( FP_SHIFT - ( x >> FP_SHIFT ) );
}