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
 int CT_COMPOSITE ; 
 int CT_RGB ; 
 int /*<<< orphan*/  PCTRA ; 
 int /*<<< orphan*/  PDTRA ; 
 int /*<<< orphan*/  VOUTC ; 
 int cable_type ; 
 int fb_readl (int /*<<< orphan*/ ) ; 
 int fb_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pvr2_init_cable(void)
{
	if (cable_type < 0) {
		fb_writel((fb_readl(PCTRA) & 0xfff0ffff) | 0x000a0000,
	                  PCTRA);
		cable_type = (fb_readw(PDTRA) >> 8) & 3;
	}

	/* Now select the output format (either composite or other) */
	/* XXX: Save the previous val first, as this reg is also AICA
	  related */
	if (cable_type == CT_COMPOSITE)
		fb_writel(3 << 8, VOUTC);
	else if (cable_type == CT_RGB)
		fb_writel(1 << 9, VOUTC);
	else
		fb_writel(0, VOUTC);

	return cable_type;
}