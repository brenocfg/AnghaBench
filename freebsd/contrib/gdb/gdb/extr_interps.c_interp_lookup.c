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
struct interp {int /*<<< orphan*/  name; struct interp* next; } ;

/* Variables and functions */
 struct interp* interp_list ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 

struct interp *
interp_lookup (const char *name)
{
  struct interp *interp;

  if (name == NULL || strlen (name) == 0)
    return NULL;

  for (interp = interp_list; interp != NULL; interp = interp->next)
    {
      if (strcmp (interp->name, name) == 0)
	return interp;
    }

  return NULL;
}