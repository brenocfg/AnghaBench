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
typedef  int /*<<< orphan*/  bfd_target ;

/* Variables and functions */
 int /*<<< orphan*/ ** bfd_target_vector ; 

const bfd_target *
bfd_search_for_target (int (*search_func) (const bfd_target *, void *),
		       void *data)
{
  const bfd_target * const *target;

  for (target = bfd_target_vector; *target != NULL; target ++)
    if (search_func (*target, data))
      return *target;

  return NULL;
}