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
struct TYPE_4__ {int /*<<< orphan*/  exp; int /*<<< orphan*/  sig; int /*<<< orphan*/  sig_hi; int /*<<< orphan*/  sig_lo; } ;
typedef  TYPE_1__ sreal ;

/* Variables and functions */

__attribute__((used)) static inline void
copy (sreal *r, sreal *a)
{
#if SREAL_PART_BITS < 32
  r->sig_lo = a->sig_lo;
  r->sig_hi = a->sig_hi;
#else
  r->sig = a->sig;
#endif
  r->exp = a->exp;
}