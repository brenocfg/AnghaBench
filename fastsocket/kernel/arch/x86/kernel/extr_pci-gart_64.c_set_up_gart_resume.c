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
typedef  void* u32 ;

/* Variables and functions */
 void* aperture_alloc ; 
 void* aperture_order ; 
 int fix_up_north_bridges ; 

void set_up_gart_resume(u32 aper_order, u32 aper_alloc)
{
	fix_up_north_bridges = true;
	aperture_order = aper_order;
	aperture_alloc = aper_alloc;
}