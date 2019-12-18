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
struct elfNN_ia64_dyn_sym_info {scalar_t__ addend; } ;

/* Variables and functions */

__attribute__((used)) static int
addend_compare (const void *xp, const void *yp)
{
  const struct elfNN_ia64_dyn_sym_info *x
    = (const struct elfNN_ia64_dyn_sym_info *) xp;
  const struct elfNN_ia64_dyn_sym_info *y
    = (const struct elfNN_ia64_dyn_sym_info *) yp;

  return x->addend < y->addend ? -1 : x->addend > y->addend ? 1 : 0;
}