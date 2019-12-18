#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned long* sig; } ;
typedef  TYPE_1__ REAL_VALUE_TYPE ;

/* Variables and functions */
 int SIGSZ ; 

__attribute__((used)) static inline bool
sub_significands (REAL_VALUE_TYPE *r, const REAL_VALUE_TYPE *a,
		  const REAL_VALUE_TYPE *b, int carry)
{
  int i;

  for (i = 0; i < SIGSZ; ++i)
    {
      unsigned long ai = a->sig[i];
      unsigned long ri = ai - b->sig[i];

      if (carry)
	{
	  carry = ri > ai;
	  carry |= ~--ri == 0;
	}
      else
	carry = ri > ai;

      r->sig[i] = ri;
    }

  return carry;
}