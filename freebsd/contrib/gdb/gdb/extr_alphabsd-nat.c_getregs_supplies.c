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
 int ALPHA_V0_REGNUM ; 
 int ALPHA_ZERO_REGNUM ; 
 int PC_REGNUM ; 

__attribute__((used)) static int
getregs_supplies (int regno)
{
  return ((regno >= ALPHA_V0_REGNUM && regno <= ALPHA_ZERO_REGNUM)
	  || regno >= PC_REGNUM);
}