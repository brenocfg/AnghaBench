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

/* Variables and functions */
 int /*<<< orphan*/  dbg_initialized ; 

void _break(void)
{
	if(!dbg_initialized) return;
	__asm__ __volatile__ (".globl __breakinst\n\
						   __breakinst: .long 0x7d821008");
}