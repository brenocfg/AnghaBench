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
 int NOISE_SIZE ; 
 scalar_t__ RAND_MAX ; 
 float rand () ; 
 unsigned char* s_noise_perm ; 
 float* s_noise_table ; 
 int /*<<< orphan*/  srand (int) ; 

void R_NoiseInit( void )
{
	int i;

	srand( 1001 );

	for ( i = 0; i < NOISE_SIZE; i++ )
	{
		s_noise_table[i] = ( float ) ( ( ( rand() / ( float ) RAND_MAX ) * 2.0 - 1.0 ) );
		s_noise_perm[i] = ( unsigned char ) ( rand() / ( float ) RAND_MAX * 255 );
	}
}