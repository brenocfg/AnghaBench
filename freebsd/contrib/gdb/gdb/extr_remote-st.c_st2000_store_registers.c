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
 int PC_REGNUM ; 
 int /*<<< orphan*/  registers_changed () ; 
 int /*<<< orphan*/  st2000_store_register (int) ; 

__attribute__((used)) static void
st2000_store_registers (void)
{
  int regno;

  for (regno = 0; regno <= PC_REGNUM; regno++)
    st2000_store_register (regno);

  registers_changed ();
}