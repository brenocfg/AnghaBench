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

__attribute__((used)) static CORE_ADDR
ia64_read_pc (ptid_t ptid)
{
  CORE_ADDR psr_value = read_register_pid (IA64_PSR_REGNUM, ptid);
  CORE_ADDR pc_value   = read_register_pid (IA64_IP_REGNUM, ptid);
  int slot_num = (psr_value >> 41) & 3;

  return pc_value | (slot_num * SLOT_MULTIPLIER);
}