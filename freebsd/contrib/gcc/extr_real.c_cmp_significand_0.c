#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* sig; } ;
typedef  TYPE_1__ REAL_VALUE_TYPE ;

/* Variables and functions */
 int SIGSZ ; 

__attribute__((used)) static inline int
cmp_significand_0 (const REAL_VALUE_TYPE *a)
{
  int i;

  for (i = SIGSZ - 1; i >= 0; --i)
    if (a->sig[i])
      return 1;

  return 0;
}