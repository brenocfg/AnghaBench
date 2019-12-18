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
typedef  scalar_t__ bfd_signed_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_2__ {unsigned int size; int /*<<< orphan*/  definition; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,long,long) ; 
 char* stab_pop_type (struct stab_write_handle*) ; 
 int /*<<< orphan*/  stab_push_string (struct stab_write_handle*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ xmalloc (scalar_t__) ; 

__attribute__((used)) static bfd_boolean
stab_range_type (void *p, bfd_signed_vma low, bfd_signed_vma high)
{
  struct stab_write_handle *info = (struct stab_write_handle *) p;
  bfd_boolean definition;
  unsigned int size;
  char *s, *buf;

  definition = info->type_stack->definition;
  size = info->type_stack->size;

  s = stab_pop_type (info);
  buf = (char *) xmalloc (strlen (s) + 100);
  sprintf (buf, "r%s;%ld;%ld;", s, (long) low, (long) high);
  free (s);

  if (! stab_push_string (info, buf, 0, definition, size))
    return FALSE;

  free (buf);

  return TRUE;
}