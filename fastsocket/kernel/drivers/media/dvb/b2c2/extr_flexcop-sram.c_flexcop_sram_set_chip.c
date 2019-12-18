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
struct flexcop_device {int dummy; } ;
typedef  int /*<<< orphan*/  flexcop_sram_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  flexcop_set_ibi_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sram_chip ; 
 int /*<<< orphan*/  wan_ctrl_reg_71c ; 

__attribute__((used)) static void flexcop_sram_set_chip(struct flexcop_device *fc,
		flexcop_sram_type_t type)
{
	flexcop_set_ibi_value(wan_ctrl_reg_71c, sram_chip, type);
}