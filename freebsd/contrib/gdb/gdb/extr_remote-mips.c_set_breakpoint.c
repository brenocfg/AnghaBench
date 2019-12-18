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
typedef  enum break_type { ____Placeholder_break_type } break_type ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int common_breakpoint (int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
set_breakpoint (CORE_ADDR addr, int len, enum break_type type)
{
  return common_breakpoint (1, addr, len, type);
}