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
 int MEMORY_REMOVE_BREAKPOINT (int /*<<< orphan*/ ,char*) ; 

int
memory_remove_breakpoint (CORE_ADDR addr, char *contents_cache)
{
  return MEMORY_REMOVE_BREAKPOINT(addr, contents_cache);
}