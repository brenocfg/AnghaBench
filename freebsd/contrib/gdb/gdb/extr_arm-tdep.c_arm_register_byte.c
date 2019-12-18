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
 int ARM_F0_REGNUM ; 
 int ARM_FPS_REGNUM ; 
 int ARM_PS_REGNUM ; 
 int FP_REGISTER_SIZE ; 
 int INT_REGISTER_SIZE ; 
 int NUM_FREGS ; 
 int NUM_GREGS ; 
 int STATUS_REGISTER_SIZE ; 

__attribute__((used)) static int
arm_register_byte (int regnum)
{
  if (regnum < ARM_F0_REGNUM)
    return regnum * INT_REGISTER_SIZE;
  else if (regnum < ARM_PS_REGNUM)
    return (NUM_GREGS * INT_REGISTER_SIZE
	    + (regnum - ARM_F0_REGNUM) * FP_REGISTER_SIZE);
  else
    return (NUM_GREGS * INT_REGISTER_SIZE
	    + NUM_FREGS * FP_REGISTER_SIZE
	    + (regnum - ARM_FPS_REGNUM) * STATUS_REGISTER_SIZE);
}