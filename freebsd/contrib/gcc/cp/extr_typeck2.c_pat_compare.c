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
typedef  scalar_t__ tree ;
struct pending_abstract_type {scalar_t__ type; } ;

/* Variables and functions */

__attribute__((used)) static int
pat_compare (const void* val1, const void* val2)
{
  const struct pending_abstract_type *pat1 =
     (const struct pending_abstract_type *) val1;
  tree type2 = (tree)val2;

  return (pat1->type == type2);
}