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
struct TYPE_2__ {char* methods; int /*<<< orphan*/ * fields; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ xmalloc (int) ; 
 scalar_t__ xrealloc (char*,int) ; 

__attribute__((used)) static bfd_boolean
stab_class_start_method (void *p, const char *name)
{
  struct stab_write_handle *info = (struct stab_write_handle *) p;
  char *m;

  assert (info->type_stack != NULL && info->type_stack->fields != NULL);

  if (info->type_stack->methods == NULL)
    {
      m = (char *) xmalloc (strlen (name) + 3);
      *m = '\0';
    }
  else
    {
      m = (char *) xrealloc (info->type_stack->methods,
			     (strlen (info->type_stack->methods)
			      + strlen (name)
			      + 4));
    }

  sprintf (m + strlen (m), "%s::", name);

  info->type_stack->methods = m;

  return TRUE;
}