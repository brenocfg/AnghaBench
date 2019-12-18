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
struct TYPE_4__ {scalar_t__ exp; scalar_t__ sig_hi; scalar_t__ sig_lo; scalar_t__ sig; } ;
typedef  TYPE_1__ sreal ;

/* Variables and functions */

int
sreal_compare (sreal *a, sreal *b)
{
  if (a->exp > b->exp)
    return 1;
  if (a->exp < b->exp)
    return -1;
#if SREAL_PART_BITS < 32
  if (a->sig_hi > b->sig_hi)
    return 1;
  if (a->sig_hi < b->sig_hi)
    return -1;
  if (a->sig_lo > b->sig_lo)
    return 1;
  if (a->sig_lo < b->sig_lo)
    return -1;
#else
  if (a->sig > b->sig)
    return 1;
  if (a->sig < b->sig)
    return -1;
#endif
  return 0;
}