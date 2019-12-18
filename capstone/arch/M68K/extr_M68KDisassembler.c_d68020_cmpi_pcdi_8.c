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
 int /*<<< orphan*/  LIMIT_CPU_TYPES (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M68010_PLUS ; 
 int /*<<< orphan*/  M68K_INS_CMPI ; 
 int /*<<< orphan*/  build_imm_ea (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_imm_8 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void d68020_cmpi_pcdi_8(m68k_info *info)
{
	LIMIT_CPU_TYPES(info, M68010_PLUS);
	build_imm_ea(info, M68K_INS_CMPI, 1, read_imm_8(info));
}