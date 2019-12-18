#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {unsigned int n; } ;
struct TYPE_3__ {unsigned int n; } ;

/* Variables and functions */
 size_t REGSET_XSTATE ; 
 size_t USER_XSTATE_XCR0_WORD ; 
 TYPE_2__* x86_32_regsets ; 
 TYPE_1__* x86_64_regsets ; 
 int /*<<< orphan*/ * xstate_fx_sw_bytes ; 

void update_regset_xstate_info(unsigned int size, u64 xstate_mask)
{
#ifdef CONFIG_X86_64
	x86_64_regsets[REGSET_XSTATE].n = size / sizeof(u64);
#endif
#if defined CONFIG_X86_32 || defined CONFIG_IA32_EMULATION
	x86_32_regsets[REGSET_XSTATE].n = size / sizeof(u64);
#endif
	xstate_fx_sw_bytes[USER_XSTATE_XCR0_WORD] = xstate_mask;
}