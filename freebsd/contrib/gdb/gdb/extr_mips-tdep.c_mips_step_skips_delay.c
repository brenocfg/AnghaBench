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
 int MIPS_INSTLEN ; 
 scalar_t__ extract_unsigned_integer (char*,int) ; 
 int is_delayed (unsigned long) ; 
 scalar_t__ pc_is_mips16 (int /*<<< orphan*/ ) ; 
 scalar_t__ target_read_memory (int /*<<< orphan*/ ,char*,int) ; 

int
mips_step_skips_delay (CORE_ADDR pc)
{
  char buf[MIPS_INSTLEN];

  /* There is no branch delay slot on MIPS16.  */
  if (pc_is_mips16 (pc))
    return 0;

  if (target_read_memory (pc, buf, MIPS_INSTLEN) != 0)
    /* If error reading memory, guess that it is not a delayed branch.  */
    return 0;
  return is_delayed ((unsigned long)
		     extract_unsigned_integer (buf, MIPS_INSTLEN));
}