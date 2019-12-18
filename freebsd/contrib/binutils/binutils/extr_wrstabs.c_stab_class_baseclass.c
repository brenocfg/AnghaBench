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
struct stab_write_handle {TYPE_1__* type_stack; } ;
typedef  enum debug_visibility { ____Placeholder_debug_visibility } debug_visibility ;
typedef  scalar_t__ bfd_vma ;
typedef  scalar_t__ bfd_boolean ;
struct TYPE_2__ {char** baseclasses; scalar_t__ definition; int /*<<< orphan*/ * fields; } ;

/* Variables and functions */
#define  DEBUG_VISIBILITY_PRIVATE 130 
#define  DEBUG_VISIBILITY_PROTECTED 129 
#define  DEBUG_VISIBILITY_PUBLIC 128 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,long,char*) ; 
 char* stab_pop_type (struct stab_write_handle*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ xmalloc (scalar_t__) ; 
 scalar_t__ xrealloc (char**,unsigned int) ; 

__attribute__((used)) static bfd_boolean
stab_class_baseclass (void *p, bfd_vma bitpos, bfd_boolean virtual,
		      enum debug_visibility visibility)
{
  struct stab_write_handle *info = (struct stab_write_handle *) p;
  bfd_boolean definition;
  char *s;
  char *buf;
  unsigned int c;
  char **baseclasses;

  definition = info->type_stack->definition;
  s = stab_pop_type (info);

  /* Build the base class specifier.  */

  buf = (char *) xmalloc (strlen (s) + 25);
  buf[0] = virtual ? '1' : '0';
  switch (visibility)
    {
    default:
      abort ();

    case DEBUG_VISIBILITY_PRIVATE:
      buf[1] = '0';
      break;

    case DEBUG_VISIBILITY_PROTECTED:
      buf[1] = '1';
      break;

    case DEBUG_VISIBILITY_PUBLIC:
      buf[1] = '2';
      break;
    }

  sprintf (buf + 2, "%ld,%s;", (long) bitpos, s);
  free (s);

  /* Add the new baseclass to the existing ones.  */

  assert (info->type_stack != NULL && info->type_stack->fields != NULL);

  if (info->type_stack->baseclasses == NULL)
    c = 0;
  else
    {
      c = 0;
      while (info->type_stack->baseclasses[c] != NULL)
	++c;
    }

  baseclasses = (char **) xrealloc (info->type_stack->baseclasses,
				    (c + 2) * sizeof (*baseclasses));
  baseclasses[c] = buf;
  baseclasses[c + 1] = NULL;

  info->type_stack->baseclasses = baseclasses;

  if (definition)
    info->type_stack->definition = TRUE;

  return TRUE;
}