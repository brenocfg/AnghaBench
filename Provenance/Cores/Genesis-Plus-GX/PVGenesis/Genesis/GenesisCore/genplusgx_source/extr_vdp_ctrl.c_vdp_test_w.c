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
 int /*<<< orphan*/  M68K_REG_PC ; 
 int /*<<< orphan*/  error (char*,unsigned int,char*) ; 
 char* m68k_get_reg (int /*<<< orphan*/ ) ; 

void vdp_test_w(unsigned int data)
{
#ifdef LOGERROR
  error("Unused VDP Write 0x%x (%08x)\n", data, m68k_get_reg(M68K_REG_PC));
#endif
}