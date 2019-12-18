#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mtd_info {int dummy; } ;
struct TYPE_3__ {int rdy; } ;
typedef  TYPE_1__ reg_pio_r_din ;

/* Variables and functions */
 TYPE_1__ REG_RD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pio ; 
 int /*<<< orphan*/  r_din ; 
 int /*<<< orphan*/  regi_pio ; 

__attribute__((used)) static int crisv32_device_ready(struct mtd_info *mtd)
{
	reg_pio_r_din din = REG_RD(pio, regi_pio, r_din);
	return din.rdy;
}