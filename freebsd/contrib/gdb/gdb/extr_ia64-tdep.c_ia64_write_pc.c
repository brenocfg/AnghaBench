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
typedef  int /*<<< orphan*/  ptid_t ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  IA64_IP_REGNUM ; 
 int /*<<< orphan*/  IA64_PSR_REGNUM ; 
 int SLOT_MULTIPLIER ; 
 int read_register_pid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_register_pid (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
ia64_write_pc (CORE_ADDR new_pc, ptid_t ptid)
{
  int slot_num = (int) (new_pc & 0xf) / SLOT_MULTIPLIER;
  CORE_ADDR psr_value = read_register_pid (IA64_PSR_REGNUM, ptid);
  psr_value &= ~(3LL << 41);
  psr_value |= (CORE_ADDR)(slot_num & 0x3) << 41;

  new_pc &= ~0xfLL;

  write_register_pid (IA64_PSR_REGNUM, psr_value, ptid);
  write_register_pid (IA64_IP_REGNUM, new_pc, ptid);
}