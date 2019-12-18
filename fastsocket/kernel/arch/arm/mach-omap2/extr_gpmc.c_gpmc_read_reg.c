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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_readl (scalar_t__) ; 
 scalar_t__ gpmc_base ; 

__attribute__((used)) static u32 gpmc_read_reg(int idx)
{
	return __raw_readl(gpmc_base + idx);
}