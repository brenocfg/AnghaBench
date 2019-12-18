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
struct gdbarch_tdep {unsigned int mips_default_saved_regsize; } ;

/* Variables and functions */
 scalar_t__ mips_saved_regsize_string ; 
 scalar_t__ size_64 ; 
 scalar_t__ size_auto ; 

__attribute__((used)) static unsigned int
mips_saved_regsize (struct gdbarch_tdep *tdep)
{
  if (mips_saved_regsize_string == size_auto)
    return tdep->mips_default_saved_regsize;
  else if (mips_saved_regsize_string == size_64)
    return 8;
  else				/* if (mips_saved_regsize_string == size_32) */
    return 4;
}