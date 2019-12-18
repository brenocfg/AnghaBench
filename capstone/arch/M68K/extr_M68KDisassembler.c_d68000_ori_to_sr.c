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
typedef  int /*<<< orphan*/  m68k_info ;

/* Variables and functions */
 int /*<<< orphan*/  M68K_INS_ORI ; 
 int /*<<< orphan*/  M68K_REG_SR ; 
 int /*<<< orphan*/  build_imm_special_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_imm_16 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void d68000_ori_to_sr(m68k_info *info)
{
	build_imm_special_reg(info, M68K_INS_ORI, read_imm_16(info), 2, M68K_REG_SR);
}