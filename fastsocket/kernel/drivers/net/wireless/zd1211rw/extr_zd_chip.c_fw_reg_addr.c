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
typedef  int /*<<< orphan*/  zd_addr_t ;
typedef  scalar_t__ u16 ;
struct zd_chip {scalar_t__ fw_regs_base; } ;

/* Variables and functions */

__attribute__((used)) static zd_addr_t fw_reg_addr(struct zd_chip *chip, u16 offset)
{
	return (zd_addr_t)((u16)chip->fw_regs_base + offset);
}