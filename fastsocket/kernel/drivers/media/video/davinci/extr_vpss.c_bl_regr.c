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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ vpss_bl_regs_base; } ;

/* Variables and functions */
 scalar_t__ __raw_readl (scalar_t__) ; 
 TYPE_1__ oper_cfg ; 

__attribute__((used)) static inline u32 bl_regr(u32 offset)
{
	return __raw_readl(oper_cfg.vpss_bl_regs_base + offset);
}