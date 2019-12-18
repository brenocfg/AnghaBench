#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long* sig; } ;
typedef  TYPE_1__ REAL_VALUE_TYPE ;

/* Variables and functions */
 int SIGSZ ; 

__attribute__((used)) static inline void
neg_significand (REAL_VALUE_TYPE *r, const REAL_VALUE_TYPE *a)
{
  bool carry = true;
  int i;

  for (i = 0; i < SIGSZ; ++i)
    {
      unsigned long ri, ai = a->sig[i];

      if (carry)
	{
	  if (ai)
	    {
	      ri = -ai;
	      carry = false;
	    }
	  else
	    ri = ai;
	}
      else
	ri = ~ai;

      r->sig[i] = ri;
    }
}