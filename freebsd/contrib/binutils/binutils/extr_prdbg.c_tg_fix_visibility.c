#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pr_handle {TYPE_1__* stack; } ;
typedef  enum debug_visibility { ____Placeholder_debug_visibility } debug_visibility ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_2__ {int visibility; } ;

/* Variables and functions */
 scalar_t__ DEBUG_VISIBILITY_IGNORE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static bfd_boolean
tg_fix_visibility (struct pr_handle *info, enum debug_visibility visibility)
{
  assert (info->stack != NULL);

  if (info->stack->visibility == visibility)
    return TRUE;

  assert (info->stack->visibility != DEBUG_VISIBILITY_IGNORE);

  info->stack->visibility = visibility;

  return TRUE;
}