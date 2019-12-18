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
 unsigned int FP0_REGNUM ; 
 int /*<<< orphan*/  i387_fill_fsave (char*,int) ; 
 int /*<<< orphan*/  npx ; 
 int /*<<< orphan*/  store_register (unsigned int) ; 

__attribute__((used)) static void
go32_store_registers (int regno)
{
  unsigned r;

  if (regno >= 0)
    store_register (regno);
  else
    {
      for (r = 0; r < FP0_REGNUM; r++)
	store_register (r);
      i387_fill_fsave ((char *) &npx, -1);
    }
}