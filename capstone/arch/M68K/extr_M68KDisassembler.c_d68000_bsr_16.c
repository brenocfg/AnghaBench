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
 int /*<<< orphan*/  M68K_INS_BSR ; 
 int /*<<< orphan*/  build_relative_branch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_int_16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_imm_16 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void d68000_bsr_16(m68k_info *info)
{
	build_relative_branch(info, M68K_INS_BSR, 2, make_int_16(read_imm_16(info)));
}