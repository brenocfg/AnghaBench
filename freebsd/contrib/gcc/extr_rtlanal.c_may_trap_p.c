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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int may_trap_p_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
may_trap_p (rtx x)
{
  return may_trap_p_1 (x, 0);
}