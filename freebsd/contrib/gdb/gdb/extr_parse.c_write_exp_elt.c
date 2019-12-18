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
typedef  union exp_element {int dummy; } exp_element ;
struct expression {union exp_element* elts; } ;

/* Variables and functions */
 scalar_t__ EXP_ELEM_TO_BYTES (int) ; 
 struct expression* expout ; 
 int expout_ptr ; 
 int expout_size ; 
 scalar_t__ xrealloc (char*,scalar_t__) ; 

void
write_exp_elt (union exp_element expelt)
{
  if (expout_ptr >= expout_size)
    {
      expout_size *= 2;
      expout = (struct expression *)
	xrealloc ((char *) expout, sizeof (struct expression)
		  + EXP_ELEM_TO_BYTES (expout_size));
    }
  expout->elts[expout_ptr++] = expelt;
}