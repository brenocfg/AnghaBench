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
 int /*<<< orphan*/  M68K_INS_ADDQ ; 
 int /*<<< orphan*/  build_3bit_ea (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void d68000_addq_32(m68k_info *info)
{
	build_3bit_ea(info, M68K_INS_ADDQ, 4);
}