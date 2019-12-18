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
struct type {int dummy; } ;
struct gdbarch {int dummy; } ;

/* Variables and functions */
 int ARM_F0_REGNUM ; 
 scalar_t__ BFD_ENDIAN_BIG ; 
 int NUM_FREGS ; 
 scalar_t__ TARGET_BYTE_ORDER ; 
 struct type* builtin_type_arm_ext_big ; 
 struct type* builtin_type_arm_ext_littlebyte_bigword ; 
 struct type* builtin_type_int32 ; 

__attribute__((used)) static struct type *
arm_register_type (struct gdbarch *gdbarch, int regnum)
{
  if (regnum >= ARM_F0_REGNUM && regnum < ARM_F0_REGNUM + NUM_FREGS)
    {
      if (TARGET_BYTE_ORDER == BFD_ENDIAN_BIG)
	return builtin_type_arm_ext_big;
      else
	return builtin_type_arm_ext_littlebyte_bigword;
    }
  else
    return builtin_type_int32;
}