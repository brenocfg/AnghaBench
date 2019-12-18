#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct rate_shaping_vars_per_vn {int dummy; } ;
struct fairness_vars_per_vn {int dummy; } ;
struct cmng_struct_per_port {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * vnic_min_rate; int /*<<< orphan*/ * vnic_max_rate; } ;
struct cmng_init {TYPE_1__ vnic; int /*<<< orphan*/  port; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ BAR_XSTRORM_INTMEM ; 
 int BP_MAX_VN_NUM (struct bnx2x*) ; 
 int VN_0 ; 
 scalar_t__ XSTORM_CMNG_PER_PORT_VARS_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ XSTORM_FAIRNESS_PER_VN_VARS_OFFSET (int) ; 
 scalar_t__ XSTORM_RATE_SHAPING_PER_VN_VARS_OFFSET (int) ; 
 int /*<<< orphan*/  __storm_memset_struct (struct bnx2x*,scalar_t__,size_t,scalar_t__*) ; 
 int func_by_vn (struct bnx2x*,int) ; 

__attribute__((used)) static void storm_memset_cmng(struct bnx2x *bp,
			      struct cmng_init *cmng,
			      u8 port)
{
	int vn;
	size_t size = sizeof(struct cmng_struct_per_port);

	u32 addr = BAR_XSTRORM_INTMEM +
			XSTORM_CMNG_PER_PORT_VARS_OFFSET(port);

	__storm_memset_struct(bp, addr, size, (u32 *)&cmng->port);

	for (vn = VN_0; vn < BP_MAX_VN_NUM(bp); vn++) {
		int func = func_by_vn(bp, vn);

		addr = BAR_XSTRORM_INTMEM +
		       XSTORM_RATE_SHAPING_PER_VN_VARS_OFFSET(func);
		size = sizeof(struct rate_shaping_vars_per_vn);
		__storm_memset_struct(bp, addr, size,
				      (u32 *)&cmng->vnic.vnic_max_rate[vn]);

		addr = BAR_XSTRORM_INTMEM +
		       XSTORM_FAIRNESS_PER_VN_VARS_OFFSET(func);
		size = sizeof(struct fairness_vars_per_vn);
		__storm_memset_struct(bp, addr, size,
				      (u32 *)&cmng->vnic.vnic_min_rate[vn]);
	}
}