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
 long* ROQ_UB_tab ; 
 long* ROQ_UG_tab ; 
 long* ROQ_VG_tab ; 
 long* ROQ_VR_tab ; 
 long* ROQ_YY_tab ; 

__attribute__((used)) static void ROQ_GenYUVTables( void )
{
	float t_ub,t_vr,t_ug,t_vg;
	long i;

	t_ub = (1.77200f/2.0f) * (float)(1<<6) + 0.5f;
	t_vr = (1.40200f/2.0f) * (float)(1<<6) + 0.5f;
	t_ug = (0.34414f/2.0f) * (float)(1<<6) + 0.5f;
	t_vg = (0.71414f/2.0f) * (float)(1<<6) + 0.5f;
	for(i=0;i<256;i++) {
		float x = (float)(2 * i - 255);
	
		ROQ_UB_tab[i] = (long)( ( t_ub * x) + (1<<5));
		ROQ_VR_tab[i] = (long)( ( t_vr * x) + (1<<5));
		ROQ_UG_tab[i] = (long)( (-t_ug * x)		 );
		ROQ_VG_tab[i] = (long)( (-t_vg * x) + (1<<5));
		ROQ_YY_tab[i] = (long)( (i << 6) | (i >> 2) );
	}
}