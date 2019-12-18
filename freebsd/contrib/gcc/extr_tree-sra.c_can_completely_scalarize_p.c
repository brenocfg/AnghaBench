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
struct sra_elt {struct sra_elt* sibling; struct sra_elt* groups; struct sra_elt* children; scalar_t__ cannot_scalarize; } ;

/* Variables and functions */

__attribute__((used)) static bool
can_completely_scalarize_p (struct sra_elt *elt)
{
  struct sra_elt *c;

  if (elt->cannot_scalarize)
    return false;

  for (c = elt->children; c; c = c->sibling)
    if (!can_completely_scalarize_p (c))
      return false;

  for (c = elt->groups; c; c = c->sibling)
    if (!can_completely_scalarize_p (c))
      return false;

  return true;
}