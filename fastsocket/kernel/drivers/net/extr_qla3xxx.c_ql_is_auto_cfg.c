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
typedef  int u16 ;
struct ql3_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ql_mii_read_reg (struct ql3_adapter*,int,int*) ; 

__attribute__((used)) static int ql_is_auto_cfg(struct ql3_adapter *qdev)
{
	u16 reg;
	ql_mii_read_reg(qdev, 0x00, &reg);
	return (reg & 0x1000) != 0;
}