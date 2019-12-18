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
typedef  int bfd_boolean ;
struct TYPE_2__ {int definition; } ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 char* stab_pop_type (struct stab_write_handle*) ; 
 int /*<<< orphan*/  stab_push_string (struct stab_write_handle*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ xmalloc (scalar_t__) ; 

__attribute__((used)) static bfd_boolean
stab_offset_type (void *p)
{
  struct stab_write_handle *info = (struct stab_write_handle *) p;
  bfd_boolean definition;
  char *target, *base, *buf;

  definition = info->type_stack->definition;
  target = stab_pop_type (info);

  definition = definition || info->type_stack->definition;
  base = stab_pop_type (info);

  buf = (char *) xmalloc (strlen (target) + strlen (base) + 3);
  sprintf (buf, "@%s,%s", base, target);
  free (base);
  free (target);

  if (! stab_push_string (info, buf, 0, definition, 0))
    return FALSE;

  free (buf);

  return TRUE;
}