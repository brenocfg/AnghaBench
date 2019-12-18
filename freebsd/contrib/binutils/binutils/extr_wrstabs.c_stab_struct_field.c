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
struct stab_write_handle {TYPE_1__* type_stack; int /*<<< orphan*/  abfd; } ;
typedef  enum debug_visibility { ____Placeholder_debug_visibility } debug_visibility ;
typedef  unsigned int bfd_vma ;
typedef  scalar_t__ bfd_boolean ;
struct TYPE_2__ {unsigned int size; char* fields; scalar_t__ definition; } ;

/* Variables and functions */
#define  DEBUG_VISIBILITY_PRIVATE 130 
#define  DEBUG_VISIBILITY_PROTECTED 129 
#define  DEBUG_VISIBILITY_PUBLIC 128 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  non_fatal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char const*,char const*,char*,long,long) ; 
 char* stab_pop_type (struct stab_write_handle*) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ xmalloc (scalar_t__) ; 

__attribute__((used)) static bfd_boolean
stab_struct_field (void *p, const char *name, bfd_vma bitpos,
		   bfd_vma bitsize, enum debug_visibility visibility)
{
  struct stab_write_handle *info = (struct stab_write_handle *) p;
  bfd_boolean definition;
  unsigned int size;
  char *s, *n;
  const char *vis;

  definition = info->type_stack->definition;
  size = info->type_stack->size;
  s = stab_pop_type (info);

  /* Add this field to the end of the current struct fields, which is
     currently on the top of the stack.  */

  assert (info->type_stack->fields != NULL);
  n = (char *) xmalloc (strlen (info->type_stack->fields)
			+ strlen (name)
			+ strlen (s)
			+ 50);

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

  if (bitsize == 0)
    {
      bitsize = size * 8;
      if (bitsize == 0)
	non_fatal (_("%s: warning: unknown size for field `%s' in struct"),
		   bfd_get_filename (info->abfd), name);
    }

  sprintf (n, "%s%s:%s%s,%ld,%ld;", info->type_stack->fields, name, vis, s,
	   (long) bitpos, (long) bitsize);

  free (info->type_stack->fields);
  info->type_stack->fields = n;

  if (definition)
    info->type_stack->definition = TRUE;

  return TRUE;
}