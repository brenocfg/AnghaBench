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
 int LONG_MAX ; 
 scalar_t__ TYPE_0 ; 
 int* end_ptr ; 
 int* fptr ; 
 scalar_t__ rand_type ; 
 int* rptr ; 
 int* state ; 

long int
random (void)
{
  if (rand_type == TYPE_0)
    {
      state[0] = ((state[0] * 1103515245) + 12345) & LONG_MAX;
      return state[0];
    }
  else
    {
      long int i;
      *fptr += *rptr;
      /* Chucking least random bit.  */
      i = (*fptr >> 1) & LONG_MAX;
      ++fptr;
      if (fptr >= end_ptr)
	{
	  fptr = state;
	  ++rptr;
	}
      else
	{
	  ++rptr;
	  if (rptr >= end_ptr)
	    rptr = state;
	}
      return i;
    }
}