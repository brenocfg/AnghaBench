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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct tstorm_eth_function_common_config {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ BAR_TSTRORM_INTMEM ; 
 scalar_t__ TSTORM_FUNCTION_COMMON_CONFIG_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __storm_memset_struct (struct bnx2x*,scalar_t__,size_t,scalar_t__*) ; 

__attribute__((used)) static void storm_memset_func_cfg(struct bnx2x *bp,
				 struct tstorm_eth_function_common_config *tcfg,
				 u16 abs_fid)
{
	size_t size = sizeof(struct tstorm_eth_function_common_config);

	u32 addr = BAR_TSTRORM_INTMEM +
			TSTORM_FUNCTION_COMMON_CONFIG_OFFSET(abs_fid);

	__storm_memset_struct(bp, addr, size, (u32 *)tcfg);
}