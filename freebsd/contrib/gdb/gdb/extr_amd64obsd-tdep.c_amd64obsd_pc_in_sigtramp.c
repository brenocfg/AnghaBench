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
typedef  int CORE_ADDR ;

/* Variables and functions */
 char* alloca (int) ; 
 int amd64obsd_page_size ; 
 scalar_t__ memcmp (char*,char const*,int) ; 
 scalar_t__ target_read_memory (int,char*,int) ; 

__attribute__((used)) static int
amd64obsd_pc_in_sigtramp (CORE_ADDR pc, char *name)
{
  CORE_ADDR start_pc = (pc & ~(amd64obsd_page_size - 1));
  const char sigreturn[] =
  {
    0x48, 0xc7, 0xc0,
    0x67, 0x00, 0x00, 0x00,	/* movq $SYS_sigreturn, %rax */
    0xcd, 0x80			/* int $0x80 */
  };
  char *buf;

  if (name)
    return 0;

  /* If we can't read the instructions at START_PC, return zero.  */
  buf = alloca (sizeof sigreturn);
  if (target_read_memory (start_pc + 0x7, buf, sizeof sigreturn))
    return 0;

  /* Check for sigreturn(2).  */
  if (memcmp (buf, sigreturn, sizeof sigreturn))
    return 0;

  return 1;
}