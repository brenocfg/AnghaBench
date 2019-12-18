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
 int OPER_I_16 () ; 
 int m68ki_get_ccr () ; 
 int /*<<< orphan*/  m68ki_set_ccr (int) ; 

__attribute__((used)) static void m68k_op_eori_16_toc(void)
{
  m68ki_set_ccr(m68ki_get_ccr() ^ OPER_I_16());
}