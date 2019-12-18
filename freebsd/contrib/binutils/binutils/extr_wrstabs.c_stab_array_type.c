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
struct stab_write_handle {long type_index; TYPE_1__* type_stack; } ;
typedef  scalar_t__ bfd_signed_vma ;
typedef  int bfd_boolean ;
struct TYPE_2__ {int definition; unsigned int size; } ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 char* stab_pop_type (struct stab_write_handle*) ; 
 int /*<<< orphan*/  stab_push_string (struct stab_write_handle*,char*,long,int,unsigned int) ; 
 int strlen (char*) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static bfd_boolean
stab_array_type (void *p, bfd_signed_vma low, bfd_signed_vma high,
		 bfd_boolean stringp)
{
  struct stab_write_handle *info = (struct stab_write_handle *) p;
  bfd_boolean definition;
  unsigned int element_size;
  char *range, *element, *buf;
  long index;
  unsigned int size;

  definition = info->type_stack->definition;
  range = stab_pop_type (info);

  definition = definition || info->type_stack->definition;
  element_size = info->type_stack->size;
  element = stab_pop_type (info);

  buf = (char *) xmalloc (strlen (range) + strlen (element) + 100);

  if (! stringp)
    {
      index = 0;
      *buf = '\0';
    }
  else
    {
      /* We need to define a type in order to include the string
         attribute.  */
      index = info->type_index;
      ++info->type_index;
      definition = TRUE;
      sprintf (buf, "%ld=@S;", index);
    }

  sprintf (buf + strlen (buf), "ar%s;%ld;%ld;%s",
	   range, (long) low, (long) high, element);
  free (range);
  free (element);

  if (high < low)
    size = 0;
  else
    size = element_size * ((high - low) + 1);
  if (! stab_push_string (info, buf, index, definition, size))
    return FALSE;

  free (buf);

  return TRUE;
}