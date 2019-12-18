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
typedef  scalar_t__ bfd_boolean ;
struct TYPE_2__ {char const* fields; scalar_t__ definition; } ;

/* Variables and functions */
#define  DEBUG_VISIBILITY_PRIVATE 130 
#define  DEBUG_VISIBILITY_PROTECTED 129 
#define  DEBUG_VISIBILITY_PUBLIC 128 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char const*,char const*,char*,char const*) ; 
 char* stab_pop_type (struct stab_write_handle*) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ xmalloc (scalar_t__) ; 

__attribute__((used)) static bfd_boolean
stab_class_static_member (void *p, const char *name, const char *physname,
			  enum debug_visibility visibility)
{
  struct stab_write_handle *info = (struct stab_write_handle *) p;
  bfd_boolean definition;
  char *s, *n;
  const char *vis;

  definition = info->type_stack->definition;
  s = stab_pop_type (info);

  /* Add this field to the end of the current struct fields, which is
     currently on the top of the stack.  */

  assert (info->type_stack->fields != NULL);
  n = (char *) xmalloc (strlen (info->type_stack->fields)
			+ strlen (name)
			+ strlen (s)
			+ strlen (physname)
			+ 10);

  switch (visibility)
    {
    default:
      abort ();

    case DEBUG_VISIBILITY_PUBLIC:
      vis = "";
      break;

    case DEBUG_VISIBILITY_PRIVATE:
      vis = "/0";
      break;

    case DEBUG_VISIBILITY_PROTECTED:
      vis = "/1";
      break;
    }

  sprintf (n, "%s%s:%s%s:%s;", info->type_stack->fields, name, vis, s,
	   physname);

  free (info->type_stack->fields);
  info->type_stack->fields = n;

  if (definition)
    info->type_stack->definition = TRUE;

  return TRUE;
}