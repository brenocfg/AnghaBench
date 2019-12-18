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
 scalar_t__ REG_AR ; 

__attribute__((used)) static int
ar_is_only_in_memory_unit (int reg)
{
  reg -= REG_AR;
  return reg >= 0 && reg <= 47;
}