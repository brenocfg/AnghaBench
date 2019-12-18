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

__attribute__((used)) static inline int
cmp_significands (const REAL_VALUE_TYPE *a, const REAL_VALUE_TYPE *b)
{
  int i;

  for (i = SIGSZ - 1; i >= 0; --i)
    {
      unsigned long ai = a->sig[i];
      unsigned long bi = b->sig[i];

      if (ai > bi)
	return 1;
      if (ai < bi)
	return -1;
    }

  return 0;
}