#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pr_handle {TYPE_2__* stack; } ;
typedef  enum debug_visibility { ____Placeholder_debug_visibility } debug_visibility ;
typedef  int bfd_boolean ;
struct TYPE_4__ {TYPE_1__* next; } ;
struct TYPE_3__ {int /*<<< orphan*/ * method; } ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ append_type (struct pr_handle*,char const*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ indent_type (struct pr_handle*) ; 
 char* pop_type (struct pr_handle*) ; 
 int /*<<< orphan*/  pr_fix_visibility (struct pr_handle*,int) ; 
 int /*<<< orphan*/  prepend_type (struct pr_handle*,char*) ; 
 int /*<<< orphan*/  substitute_type (struct pr_handle*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
pr_class_static_method_variant (void *p, const char *physname,
				enum debug_visibility visibility,
				bfd_boolean constp, bfd_boolean volatilep)
{
  struct pr_handle *info = (struct pr_handle *) p;
  char *method_type;

  assert (info->stack != NULL);
  assert (info->stack->next != NULL);
  assert (info->stack->next->method != NULL);

  /* Put the const and volatile qualifiers on the type.  */
  if (volatilep)
    {
      if (! append_type (info, " volatile"))
	return FALSE;
    }
  if (constp)
    {
      if (! append_type (info, " const"))
	return FALSE;
    }

  /* Mark it as static.  */
  if (! prepend_type (info, "static "))
    return FALSE;

  /* Stick the name of the method into its type.  */
  if (! substitute_type (info, info->stack->next->method))
    return FALSE;

  /* Get the type.  */
  method_type = pop_type (info);
  if (method_type == NULL)
    return FALSE;

  /* Now the top of the stack is the class.  */

  if (! pr_fix_visibility (info, visibility))
    return FALSE;

  return (append_type (info, method_type)
	  && append_type (info, " /* ")
	  && append_type (info, physname)
	  && append_type (info, " */;\n")
	  && indent_type (info));
}