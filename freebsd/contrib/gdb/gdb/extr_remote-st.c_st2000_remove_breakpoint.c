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
 int MAX_STDEBUG_BREAKPOINTS ; 
 scalar_t__* breakaddr ; 
 int /*<<< orphan*/  expect_prompt (int) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 int /*<<< orphan*/  printf_stdebug (char*,int) ; 

__attribute__((used)) static int
st2000_remove_breakpoint (CORE_ADDR addr, char *shadow)
{
  int i;

  for (i = 0; i < MAX_STDEBUG_BREAKPOINTS; i++)
    if (breakaddr[i] == addr)
      {
	breakaddr[i] = 0;

	printf_stdebug ("CB %d\r", i);
	expect_prompt (1);
	return 0;
      }

  fprintf_unfiltered (gdb_stderr,
		      "Can't find breakpoint associated with 0x%x\n", addr);
  return 1;
}