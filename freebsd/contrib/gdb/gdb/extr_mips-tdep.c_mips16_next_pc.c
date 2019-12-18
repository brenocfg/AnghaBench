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
 int /*<<< orphan*/  extended_mips16_next_pc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int fetch_mips_16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static CORE_ADDR
mips16_next_pc (CORE_ADDR pc)
{
  unsigned int insn = fetch_mips_16 (pc);
  return extended_mips16_next_pc (pc, 0, insn);
}