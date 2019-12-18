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
struct dum_ch_setup {int format; } ;

/* Variables and functions */
#define  RGB666 129 
#define  RGB888 128 
 int nof_pixels_dxy (struct dum_ch_setup*) ; 

__attribute__((used)) static u32 nof_bytes(struct dum_ch_setup *ch_setup)
{
	u32 r = nof_pixels_dxy(ch_setup);
	switch (ch_setup->format) {
	case RGB888:
	case RGB666:
		r *= 4;
		break;

	default:
		r *= 2;
		break;
	}
	return r;
}