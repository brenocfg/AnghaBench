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
 long get_hex_digit (int) ; 
 int /*<<< orphan*/  supply_register (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
get_hex_regs (int n, int regno)
{
  long val;
  int i;

  for (i = 0; i < n; i++)
    {
      int j;

      val = 0;
      for (j = 0; j < 8; j++)
	val = (val << 4) + get_hex_digit (j == 0);
      supply_register (regno++, (char *) &val);
    }
}