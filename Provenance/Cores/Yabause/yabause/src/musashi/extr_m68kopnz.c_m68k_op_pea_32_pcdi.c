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
typedef  int /*<<< orphan*/  uint ;

/* Variables and functions */
 int /*<<< orphan*/  EA_PCDI_32 () ; 
 int /*<<< orphan*/  m68ki_push_32 (int /*<<< orphan*/ ) ; 

void m68k_op_pea_32_pcdi(void)
{
	uint ea = EA_PCDI_32();

	m68ki_push_32(ea);
}