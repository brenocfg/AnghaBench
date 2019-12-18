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
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BREAKPOINT_FROM_PC (scalar_t__*,int*) ; 
 int MAX_STDEBUG_BREAKPOINTS ; 
 scalar_t__* breakaddr ; 
 int /*<<< orphan*/  expect_prompt (int) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 int /*<<< orphan*/  printf_stdebug (char*,scalar_t__) ; 
 int /*<<< orphan*/  st2000_read_inferior_memory (scalar_t__,char*,int) ; 

__attribute__((used)) static int
st2000_insert_breakpoint (CORE_ADDR addr, char *shadow)
{
  int i;
  CORE_ADDR bp_addr = addr;
  int bp_size = 0;

  BREAKPOINT_FROM_PC (&bp_addr, &bp_size);

  for (i = 0; i <= MAX_STDEBUG_BREAKPOINTS; i++)
    if (breakaddr[i] == 0)
      {
	breakaddr[i] = addr;

	st2000_read_inferior_memory (bp_addr, shadow, bp_size);
	printf_stdebug ("BR %x H\r", addr);
	expect_prompt (1);
	return 0;
      }

  fprintf_unfiltered (gdb_stderr, "Too many breakpoints (> 16) for STDBUG\n");
  return 1;
}