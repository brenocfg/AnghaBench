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
 int /*<<< orphan*/  M68K_INS_OR ; 
 int /*<<< orphan*/  build_re_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void d68000_or_re_8(m68k_info *info)
{
	build_re_1(info, M68K_INS_OR, 1);
}