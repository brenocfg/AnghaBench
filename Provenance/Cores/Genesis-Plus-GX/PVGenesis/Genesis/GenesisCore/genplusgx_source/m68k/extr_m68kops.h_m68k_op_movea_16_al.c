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
 int /*<<< orphan*/  AX ; 
 int /*<<< orphan*/  MAKE_INT_16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPER_AL_16 () ; 

__attribute__((used)) static void m68k_op_movea_16_al(void)
{
  AX = MAKE_INT_16(OPER_AL_16());
}