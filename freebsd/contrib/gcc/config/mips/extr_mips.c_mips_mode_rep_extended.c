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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int DImode ; 
 int SIGN_EXTEND ; 
 int SImode ; 
 scalar_t__ TARGET_64BIT ; 
 int UNKNOWN ; 

int
mips_mode_rep_extended (enum machine_mode mode, enum machine_mode mode_rep)
{
  if (TARGET_64BIT && mode == SImode && mode_rep == DImode)
    return SIGN_EXTEND;

  return UNKNOWN;
}