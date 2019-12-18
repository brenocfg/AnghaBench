#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ptid_t ;
struct TYPE_2__ {int /*<<< orphan*/  pc; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  current_gdbarch ; 
 TYPE_1__* mips_regnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_signed_register_pid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CORE_ADDR
mips_read_pc (ptid_t ptid)
{
  return read_signed_register_pid (mips_regnum (current_gdbarch)->pc, ptid);
}