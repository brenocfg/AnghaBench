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
 int /*<<< orphan*/  DX ; 
 int /*<<< orphan*/  DY ; 

__attribute__((used)) static void m68k_op_exg_32_dd(void)
{
  uint* reg_a = &DX;
  uint* reg_b = &DY;
  uint tmp = *reg_a;
  *reg_a = *reg_b;
  *reg_b = tmp;
}