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
struct TYPE_4__ {int* sig; } ;
typedef  TYPE_1__ REAL_VALUE_TYPE ;

/* Variables and functions */
 int HOST_BITS_PER_LONG ; 
 int SIGSZ ; 

__attribute__((used)) static inline void
lshift_significand_1 (REAL_VALUE_TYPE *r, const REAL_VALUE_TYPE *a)
{
  unsigned int i;

  for (i = SIGSZ - 1; i > 0; --i)
    r->sig[i] = (a->sig[i] << 1) | (a->sig[i-1] >> (HOST_BITS_PER_LONG - 1));
  r->sig[0] = a->sig[0] << 1;
}