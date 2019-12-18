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
typedef  int nes_ntsc_rgb_t ;

/* Variables and functions */
 size_t burst_size ; 
 int nes_ntsc_rgb_builder ; 
 int rgb_bias ; 

__attribute__((used)) static void merge_kernel_fields( nes_ntsc_rgb_t* io )
{
	int n;
	for ( n = burst_size; n; --n )
	{
		nes_ntsc_rgb_t p0 = io [burst_size * 0] + rgb_bias;
		nes_ntsc_rgb_t p1 = io [burst_size * 1] + rgb_bias;
		nes_ntsc_rgb_t p2 = io [burst_size * 2] + rgb_bias;
		/* merge colors without losing precision */
		io [burst_size * 0] =
				((p0 + p1 - ((p0 ^ p1) & nes_ntsc_rgb_builder)) >> 1) - rgb_bias;
		io [burst_size * 1] =
				((p1 + p2 - ((p1 ^ p2) & nes_ntsc_rgb_builder)) >> 1) - rgb_bias;
		io [burst_size * 2] =
				((p2 + p0 - ((p2 ^ p0) & nes_ntsc_rgb_builder)) >> 1) - rgb_bias;
		++io;
	}
}