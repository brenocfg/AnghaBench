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
struct fb_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ TC_NBLANK ; 
 int fb_bitmask ; 
 scalar_t__ fb_regs ; 
 int /*<<< orphan*/  out_8 (scalar_t__,int) ; 

__attribute__((used)) static int hpfb_blank(int blank, struct fb_info *info)
{
	out_8(fb_regs + TC_NBLANK, (blank ? 0x00 : fb_bitmask));

	return 0;
}