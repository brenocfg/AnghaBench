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
 int NUM_REALREGS ; 
 int /*<<< orphan*/  e7000_store_register (int) ; 
 int /*<<< orphan*/  registers_changed () ; 

__attribute__((used)) static void
e7000_store_registers (void)
{
  int regno;

  for (regno = 0; regno < NUM_REALREGS; regno++)
    e7000_store_register (regno);

  registers_changed ();
}