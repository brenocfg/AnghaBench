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
struct user {int /*<<< orphan*/ * u_fpstate; } ;

/* Variables and functions */
 int FP0_REGNUM ; 
 int* regmap ; 

int
dpx2_register_u_addr (int blockend, int regnum)
{
  if (regnum < FP0_REGNUM)
    return (blockend + 4 * regmap[regnum]);
  else
    return (int) &(((struct user *) 0)->u_fpstate[regmap[regnum]]);
}