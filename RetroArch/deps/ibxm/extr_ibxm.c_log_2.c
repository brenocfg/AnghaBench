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
 int FP_SHIFT ; 
 int exp_2 (int) ; 

__attribute__((used)) static int log_2( int x ) {
	int step;
	int y = 16 << FP_SHIFT;
	for( step = y; step > 0; step >>= 1 ) {
		if( exp_2( y - step ) >= x ) {
			y -= step;
		}
	}
	return y;
}