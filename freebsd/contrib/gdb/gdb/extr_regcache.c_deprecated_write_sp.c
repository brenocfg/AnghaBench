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
 scalar_t__ SP_REGNUM ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  write_register (scalar_t__,int /*<<< orphan*/ ) ; 

void
deprecated_write_sp (CORE_ADDR val)
{
  gdb_assert (SP_REGNUM >= 0);
  write_register (SP_REGNUM, val);
}