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

/* Variables and functions */
 int /*<<< orphan*/  DEPRECATED_REGISTER_RAW_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PC_REGNUM ; 
 char* phex_nz (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puts_e7000debug (char*) ; 
 scalar_t__ read_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  store_signed_integer (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  supply_register (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
sub2_from_pc (void)
{
  char buf[4];
  char buf2[200];

  store_signed_integer (buf,
			DEPRECATED_REGISTER_RAW_SIZE (PC_REGNUM),
			read_register (PC_REGNUM) - 2);
  supply_register (PC_REGNUM, buf);
  sprintf (buf2, ".PC %s\r", phex_nz (read_register (PC_REGNUM), 0));
  puts_e7000debug (buf2);
}