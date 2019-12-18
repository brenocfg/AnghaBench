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
 int /*<<< orphan*/  A0_REGNUM ; 
 int /*<<< orphan*/  FBSD_MIPS_JB_ELEMENT_SIZE ; 
 scalar_t__ FBSD_MIPS_JB_OFFSET ; 
 char* alloca (int /*<<< orphan*/ ) ; 
 scalar_t__ extract_unsigned_integer (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ read_register (int /*<<< orphan*/ ) ; 
 scalar_t__ target_read_memory (scalar_t__,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mipsfbsd_get_longjmp_target (CORE_ADDR *pc)
{
  CORE_ADDR jb_addr;
  char *buf;

  buf = alloca (FBSD_MIPS_JB_ELEMENT_SIZE);

  jb_addr = read_register (A0_REGNUM);

  if (target_read_memory (jb_addr + FBSD_MIPS_JB_OFFSET, buf,
  			  FBSD_MIPS_JB_ELEMENT_SIZE))
    return 0;

  *pc = extract_unsigned_integer (buf, FBSD_MIPS_JB_ELEMENT_SIZE);

  return 1;
}