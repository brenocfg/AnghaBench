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
typedef  float* vec3_t ;
typedef  float byte ;

/* Variables and functions */
 int /*<<< orphan*/  VectorCopy (float const*,float*) ; 
 int /*<<< orphan*/  VectorScale (float*,int,float*) ; 

void ColorToBytes( const float *color, byte *colorBytes ) {
	float	max;
	vec3_t	sample;

	VectorCopy( color, sample );

	// clamp with color normalization
	max = sample[0];
	if ( sample[1] > max ) {
		max = sample[1];
	}
	if ( sample[2] > max ) {
		max = sample[2];
	}
	if ( max > 255 ) {
		VectorScale( sample, 255/max, sample );
	}
	colorBytes[ 0 ] = sample[0];
	colorBytes[ 1 ] = sample[1];
	colorBytes[ 2 ] = sample[2];
}