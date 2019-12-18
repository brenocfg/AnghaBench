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
 unsigned int extract_unsigned_integer (char*,int) ; 
 int /*<<< orphan*/  memory_error (int,int /*<<< orphan*/ ) ; 
 int read_memory_nobpt (int /*<<< orphan*/ ,char*,int) ; 

unsigned int
alpha_read_insn (CORE_ADDR pc)
{
  char buf[4];
  int status;

  status = read_memory_nobpt (pc, buf, 4);
  if (status)
    memory_error (status, pc);
  return extract_unsigned_integer (buf, 4);
}