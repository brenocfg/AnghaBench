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
typedef  int u32 ;
struct dum_ch_setup {int dummy; } ;

/* Variables and functions */
 int nof_pixels_dx (struct dum_ch_setup*) ; 
 int nof_pixels_dy (struct dum_ch_setup*) ; 

__attribute__((used)) static u32 nof_pixels_dxy(struct dum_ch_setup *ch_setup)
{
	return (nof_pixels_dx(ch_setup) * nof_pixels_dy(ch_setup));
}