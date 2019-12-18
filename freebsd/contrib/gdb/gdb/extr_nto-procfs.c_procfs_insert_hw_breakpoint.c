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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int _DEBUG_BREAK_EXEC ; 
 int _DEBUG_BREAK_HW ; 
 int procfs_breakpoint (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
procfs_insert_hw_breakpoint (CORE_ADDR addr, char *contents_cache)
{
  return procfs_breakpoint (addr, _DEBUG_BREAK_EXEC | _DEBUG_BREAK_HW, 0);
}