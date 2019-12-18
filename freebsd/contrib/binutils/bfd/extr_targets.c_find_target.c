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
struct targmatch {TYPE_1__ const* vector; int /*<<< orphan*/ * triplet; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ bfd_target ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_error_invalid_target ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 struct targmatch* bfd_target_match ; 
 TYPE_1__** bfd_target_vector ; 
 scalar_t__ fnmatch (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const bfd_target *
find_target (const char *name)
{
  const bfd_target * const *target;
  const struct targmatch *match;

  for (target = &bfd_target_vector[0]; *target != NULL; target++)
    if (strcmp (name, (*target)->name) == 0)
      return *target;

  /* If we couldn't match on the exact name, try matching on the
     configuration triplet.  FIXME: We should run the triplet through
     config.sub first, but that is hard.  */
  for (match = &bfd_target_match[0]; match->triplet != NULL; match++)
    {
      if (fnmatch (match->triplet, name, 0) == 0)
	{
	  while (match->vector == NULL)
	    ++match;
	  return match->vector;
	}
    }

  bfd_set_error (bfd_error_invalid_target);
  return NULL;
}