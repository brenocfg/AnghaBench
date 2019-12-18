#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct qlcnic_adapter {TYPE_2__* ahw; } ;
struct qlc_83xx_rmw {int index_a; int mask; int shl; int shr; int or_value; int xor_value; } ;
struct TYPE_3__ {int* array; } ;
struct TYPE_4__ {TYPE_1__ reset; } ;

/* Variables and functions */
 int qlcnic_83xx_rd_reg_indirect (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_83xx_wrt_reg_indirect (struct qlcnic_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qlcnic_83xx_rmw_crb_reg(struct qlcnic_adapter *p_dev,
				    u32 raddr, u32 waddr,
				    struct qlc_83xx_rmw *p_rmw_hdr)
{
	int value;

	if (p_rmw_hdr->index_a)
		value = p_dev->ahw->reset.array[p_rmw_hdr->index_a];
	else
		value = qlcnic_83xx_rd_reg_indirect(p_dev, raddr);

	value &= p_rmw_hdr->mask;
	value <<= p_rmw_hdr->shl;
	value >>= p_rmw_hdr->shr;
	value |= p_rmw_hdr->or_value;
	value ^= p_rmw_hdr->xor_value;
	qlcnic_83xx_wrt_reg_indirect(p_dev, waddr, value);
}