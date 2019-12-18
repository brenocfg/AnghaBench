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
 unsigned int HOST_BITS_PER_LONG ; 
 unsigned int SIGSZ ; 

__attribute__((used)) static bool
sticky_rshift_significand (REAL_VALUE_TYPE *r, const REAL_VALUE_TYPE *a,
			   unsigned int n)
{
  unsigned long sticky = 0;
  unsigned int i, ofs = 0;

  if (n >= HOST_BITS_PER_LONG)
    {
      for (i = 0, ofs = n / HOST_BITS_PER_LONG; i < ofs; ++i)
	sticky |= a->sig[i];
      n &= HOST_BITS_PER_LONG - 1;
    }

  if (n != 0)
    {
      sticky |= a->sig[ofs] & (((unsigned long)1 << n) - 1);
      for (i = 0; i < SIGSZ; ++i)
	{
	  r->sig[i]
	    = (((ofs + i >= SIGSZ ? 0 : a->sig[ofs + i]) >> n)
	       | ((ofs + i + 1 >= SIGSZ ? 0 : a->sig[ofs + i + 1])
		  << (HOST_BITS_PER_LONG - n)));
	}
    }
  else
    {
      for (i = 0; ofs + i < SIGSZ; ++i)
	r->sig[i] = a->sig[ofs + i];
      for (; i < SIGSZ; ++i)
	r->sig[i] = 0;
    }

  return sticky != 0;
}