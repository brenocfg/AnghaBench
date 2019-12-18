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
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_2__ {char* fields; long index; unsigned int size; int /*<<< orphan*/  definition; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 char* stab_pop_type (struct stab_write_handle*) ; 
 int /*<<< orphan*/  stab_push_string (struct stab_write_handle*,char*,long,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ xmalloc (scalar_t__) ; 

__attribute__((used)) static bfd_boolean
stab_end_struct_type (void *p)
{
  struct stab_write_handle *info = (struct stab_write_handle *) p;
  bfd_boolean definition;
  long index;
  unsigned int size;
  char *fields, *first, *buf;

  assert (info->type_stack != NULL && info->type_stack->fields != NULL);

  definition = info->type_stack->definition;
  index = info->type_stack->index;
  size = info->type_stack->size;
  fields = info->type_stack->fields;
  first = stab_pop_type (info);

  buf = (char *) xmalloc (strlen (first) + strlen (fields) + 2);
  sprintf (buf, "%s%s;", first, fields);
  free (first);
  free (fields);

  if (! stab_push_string (info, buf, index, definition, size))
    return FALSE;

  free (buf);

  return TRUE;
}