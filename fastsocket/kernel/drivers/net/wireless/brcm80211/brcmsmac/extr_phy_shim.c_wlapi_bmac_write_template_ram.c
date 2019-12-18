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
struct phy_shim_info {int /*<<< orphan*/  wlc_hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcms_b_write_template_ram (int /*<<< orphan*/ ,int,int,void*) ; 

void
wlapi_bmac_write_template_ram(struct phy_shim_info *physhim, int offset,
			      int len, void *buf)
{
	brcms_b_write_template_ram(physhim->wlc_hw, offset, len, buf);
}