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
typedef  scalar_t__ e_type ;
typedef  scalar_t__ e_processor ;

/* Variables and functions */
 scalar_t__ e_nprocs ; 
 scalar_t__ e_nregtypes ; 
 scalar_t__ e_p0 ; 
 scalar_t__ e_regtype0 ; 
 scalar_t__ itbl_get_val (scalar_t__,scalar_t__,char*,unsigned long*) ; 

int
itbl_get_reg_val (char *name, unsigned long *pval)
{
  e_type t;
  e_processor p;

  for (p = e_p0; p < e_nprocs; p++)
    {
      for (t = e_regtype0; t < e_nregtypes; t++)
	{
	  if (itbl_get_val (p, t, name, pval))
	    return 1;
	}
    }
  return 0;
}