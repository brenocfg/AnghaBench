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
 int calculate_tick_len (int,int) ; 

int calculate_mix_buf_len( int sample_rate ) {
	return ( calculate_tick_len( 32, sample_rate ) + 65 ) * 4;
}