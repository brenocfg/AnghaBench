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
 int NUM_REGS ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  mips_error (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_map_regno (int) ; 
 int /*<<< orphan*/  mips_receive_wait ; 
 int /*<<< orphan*/  mips_request (char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_register (int) ; 
 int /*<<< orphan*/  safe_strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mips_store_registers (int regno)
{
  int err;

  if (regno == -1)
    {
      for (regno = 0; regno < NUM_REGS; regno++)
	mips_store_registers (regno);
      return;
    }

  mips_request ('R', mips_map_regno (regno),
		read_register (regno),
		&err, mips_receive_wait, NULL);
  if (err)
    mips_error ("Can't write register %d: %s", regno, safe_strerror (errno));
}