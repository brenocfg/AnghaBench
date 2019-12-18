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
struct var_map_elt {scalar_t__ old; } ;

/* Variables and functions */

__attribute__((used)) static int
var_map_eq (const void *x, const void *y)
{
  const struct var_map_elt *a = (const struct var_map_elt *) x;
  const struct var_map_elt *b = (const struct var_map_elt *) y;
  return a->old == b->old;
}