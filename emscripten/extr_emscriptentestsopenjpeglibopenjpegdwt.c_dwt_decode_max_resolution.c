#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int x1; int x0; int y1; int y0; } ;
typedef  TYPE_1__ opj_tcd_resolution_t ;

/* Variables and functions */

__attribute__((used)) static int dwt_decode_max_resolution(opj_tcd_resolution_t* restrict r, int i) {
	int mr	= 1;
	int w;
	while( --i ) {
		r++;
		if( mr < ( w = r->x1 - r->x0 ) )
			mr = w ;
		if( mr < ( w = r->y1 - r->y0 ) )
			mr = w ;
	}
	return mr ;
}