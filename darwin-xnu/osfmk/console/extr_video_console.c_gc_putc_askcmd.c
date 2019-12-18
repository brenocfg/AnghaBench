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
 int /*<<< orphan*/  ESnormal ; 
 size_t gc_numpars ; 
 int* gc_par ; 
 int gc_relative_origin ; 
 int /*<<< orphan*/  gc_vt100state ; 
 int gc_wrap_mode ; 

__attribute__((used)) static void
gc_putc_askcmd(unsigned char ch)
{
	if (ch >= '0' && ch <= '9') {
		gc_par[gc_numpars] = (10*gc_par[gc_numpars]) + (ch-'0');
		return;
	}
	gc_vt100state = ESnormal;

	switch (gc_par[0]) {
		case 6:
			gc_relative_origin = ch == 'h';
			break;
		case 7:	/* wrap around mode h=1, l=0*/
			gc_wrap_mode = ch == 'h';
			break;
		default:
			break;
	}

}