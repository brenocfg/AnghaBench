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
typedef  int u16 ;
struct vc_data {int vc_hi_font_mask; scalar_t__ vc_origin; int /*<<< orphan*/  vc_can_do_color; } ;
typedef  int a ;

/* Variables and functions */
 int scr_readw (int*) ; 
 int /*<<< orphan*/  scr_writew (int,int /*<<< orphan*/ ) ; 
 scalar_t__ softback_buf ; 
 scalar_t__ softback_end ; 
 scalar_t__ softback_in ; 

__attribute__((used)) static void fbcon_invert_region(struct vc_data *vc, u16 * p, int cnt)
{
	while (cnt--) {
		u16 a = scr_readw(p);
		if (!vc->vc_can_do_color)
			a ^= 0x0800;
		else if (vc->vc_hi_font_mask == 0x100)
			a = ((a) & 0x11ff) | (((a) & 0xe000) >> 4) |
			    (((a) & 0x0e00) << 4);
		else
			a = ((a) & 0x88ff) | (((a) & 0x7000) >> 4) |
			    (((a) & 0x0700) << 4);
		scr_writew(a, p++);
		if (p == (u16 *) softback_end)
			p = (u16 *) softback_buf;
		if (p == (u16 *) softback_in)
			p = (u16 *) vc->vc_origin;
	}
}