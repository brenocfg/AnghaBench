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
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_2__ {int /*<<< orphan*/  definition; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 char* stab_pop_type (struct stab_write_handle*) ; 
 int /*<<< orphan*/  stab_push_string (struct stab_write_handle*,char*,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static bfd_boolean
stab_set_type (void *p, bfd_boolean bitstringp)
{
  struct stab_write_handle *info = (struct stab_write_handle *) p;
  bfd_boolean definition;
  char *s, *buf;
  long index;

  definition = info->type_stack->definition;

  s = stab_pop_type (info);
  buf = (char *) xmalloc (strlen (s) + 30);

  if (! bitstringp)
    {
      *buf = '\0';
      index = 0;
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

  sprintf (buf + strlen (buf), "S%s", s);
  free (s);

  if (! stab_push_string (info, buf, index, definition, 0))
    return FALSE;

  free (buf);

  return TRUE;
}