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
struct TYPE_4__ {unsigned int* sig; } ;
typedef  TYPE_1__ REAL_VALUE_TYPE ;

/* Variables and functions */
 unsigned int HOST_BITS_PER_LONG ; 
 unsigned int SIGSZ ; 

__attribute__((used)) static void
lshift_significand (REAL_VALUE_TYPE *r, const REAL_VALUE_TYPE *a,
		    unsigned int n)
{
  unsigned int i, ofs = n / HOST_BITS_PER_LONG;

  n &= HOST_BITS_PER_LONG - 1;
  if (n == 0)
    {
      for (i = 0; ofs + i < SIGSZ; ++i)
	r->sig[SIGSZ-1-i] = a->sig[SIGSZ-1-i-ofs];
      for (; i < SIGSZ; ++i)
	r->sig[SIGSZ-1-i] = 0;
    }
  else
    for (i = 0; i < SIGSZ; ++i)
      {
	r->sig[SIGSZ-1-i]
	  = (((ofs + i >= SIGSZ ? 0 : a->sig[SIGSZ-1-i-ofs]) << n)
	     | ((ofs + i + 1 >= SIGSZ ? 0 : a->sig[SIGSZ-1-i-ofs-1])
		>> (HOST_BITS_PER_LONG - n)));
      }
}