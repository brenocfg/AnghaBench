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
struct atyfb_par {scalar_t__ ram_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  M64_HAS (int /*<<< orphan*/ ) ; 
 scalar_t__ SGRAM ; 
 scalar_t__ WRAM ; 
 int /*<<< orphan*/  XL_MEM ; 

__attribute__((used)) static u32 calc_line_length(struct atyfb_par *par, u32 vxres, u32 bpp)
{
	u32 line_length = vxres * bpp / 8;

	if (par->ram_type == SGRAM ||
	    (!M64_HAS(XL_MEM) && par->ram_type == WRAM))
		line_length = (line_length + 63) & ~63;

	return line_length;
}