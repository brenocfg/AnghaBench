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
 int /*<<< orphan*/  AY ; 
 int /*<<< orphan*/ * REG_A ; 
 int /*<<< orphan*/  m68ki_pull_32 () ; 

__attribute__((used)) static void m68k_op_unlk_32(void)
{
  uint* r_dst = &AY;

  REG_A[7] = *r_dst;
  *r_dst = m68ki_pull_32();
}