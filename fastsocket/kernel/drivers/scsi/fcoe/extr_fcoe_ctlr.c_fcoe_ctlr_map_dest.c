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
struct fcoe_ctlr {scalar_t__ mode; int map_dest; scalar_t__ dest_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIP_DEF_FC_MAP ; 
 scalar_t__ FIP_MODE_VN2VN ; 
 int /*<<< orphan*/  FIP_VN_FC_MAP ; 
 int /*<<< orphan*/  hton24 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fcoe_ctlr_map_dest(struct fcoe_ctlr *fip)
{
	if (fip->mode == FIP_MODE_VN2VN)
		hton24(fip->dest_addr, FIP_VN_FC_MAP);
	else
		hton24(fip->dest_addr, FIP_DEF_FC_MAP);
	hton24(fip->dest_addr + 3, 0);
	fip->map_dest = 1;
}