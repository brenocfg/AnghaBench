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
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ bfd_target ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__ const** bfd_default_vector ; 
 TYPE_1__* find_target (char const*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

bfd_boolean
bfd_set_default_target (const char *name)
{
  const bfd_target *target;

  if (bfd_default_vector[0] != NULL
      && strcmp (name, bfd_default_vector[0]->name) == 0)
    return TRUE;

  target = find_target (name);
  if (target == NULL)
    return FALSE;

  bfd_default_vector[0] = target;
  return TRUE;
}