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
typedef  int /*<<< orphan*/  t_inst ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int MIPS16_INSTLEN ; 
 int MIPS_INSTLEN ; 
 int /*<<< orphan*/  extract_unsigned_integer (char*,int) ; 
 int /*<<< orphan*/  memory_error (int,int /*<<< orphan*/ ) ; 
 scalar_t__ pc_is_mips16 (int /*<<< orphan*/ ) ; 
 int read_memory_nobpt (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  unmake_mips16_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static t_inst
mips_fetch_instruction (CORE_ADDR addr)
{
  char buf[MIPS_INSTLEN];
  int instlen;
  int status;

  if (pc_is_mips16 (addr))
    {
      instlen = MIPS16_INSTLEN;
      addr = unmake_mips16_addr (addr);
    }
  else
    instlen = MIPS_INSTLEN;
  status = read_memory_nobpt (addr, buf, instlen);
  if (status)
    memory_error (status, addr);
  return extract_unsigned_integer (buf, instlen);
}