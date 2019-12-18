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
 scalar_t__ find_pc_partial_function (scalar_t__,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
mips_in_return_stub (CORE_ADDR pc, char *name)
{
  CORE_ADDR start_addr;

  /* Find the starting address of the function containing the PC.  */
  if (find_pc_partial_function (pc, NULL, &start_addr, NULL) == 0)
    return 0;

  /* If the PC is in __mips16_ret_{d,s}f, this is a return stub.  */
  if (strcmp (name, "__mips16_ret_sf") == 0
      || strcmp (name, "__mips16_ret_df") == 0)
    return 1;

  /* If the PC is in __mips16_call_stub_{s,d}f_{0..10} but not at the start,
     i.e. after the jal instruction, this is effectively a return stub.  */
  if (strncmp (name, "__mips16_call_stub_", 19) == 0
      && (name[19] == 's' || name[19] == 'd') && pc != start_addr)
    return 1;

  return 0;			/* not a stub */
}