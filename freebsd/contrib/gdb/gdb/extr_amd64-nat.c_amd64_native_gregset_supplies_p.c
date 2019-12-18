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
 int amd64_native_gregset_reg_offset (int) ; 

int
amd64_native_gregset_supplies_p (int regnum)
{
  return (amd64_native_gregset_reg_offset (regnum) != -1);
}