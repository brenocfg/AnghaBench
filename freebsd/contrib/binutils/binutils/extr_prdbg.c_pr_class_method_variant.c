#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pr_handle {TYPE_3__* stack; } ;
typedef  enum debug_visibility { ____Placeholder_debug_visibility } debug_visibility ;
typedef  scalar_t__ bfd_vma ;
typedef  int bfd_boolean ;
struct TYPE_6__ {TYPE_2__* next; } ;
struct TYPE_5__ {int /*<<< orphan*/  method; TYPE_1__* next; } ;
struct TYPE_4__ {int /*<<< orphan*/  method; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ append_type (struct pr_handle*,char const*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ indent_type (struct pr_handle*) ; 
 char* pop_type (struct pr_handle*) ; 
 int /*<<< orphan*/  pr_fix_visibility (struct pr_handle*,int) ; 
 int /*<<< orphan*/  print_vma (scalar_t__,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  substitute_type (struct pr_handle*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
pr_class_method_variant (void *p, const char *physname,
			 enum debug_visibility visibility,
			 bfd_boolean constp, bfd_boolean volatilep,
			 bfd_vma voffset, bfd_boolean context)
{
  struct pr_handle *info = (struct pr_handle *) p;
  char *method_type;
  char *context_type;

  assert (info->stack != NULL);
  assert (info->stack->next != NULL);

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

  /* Stick the name of the method into its type.  */
  if (! substitute_type (info,
			 (context
			  ? info->stack->next->next->method
			  : info->stack->next->method)))
    return FALSE;

  /* Get the type.  */
  method_type = pop_type (info);
  if (method_type == NULL)
    return FALSE;

  /* Pull off the context type if there is one.  */
  if (! context)
    context_type = NULL;
  else
    {
      context_type = pop_type (info);
      if (context_type == NULL)
	return FALSE;
    }

  /* Now the top of the stack is the class.  */

  if (! pr_fix_visibility (info, visibility))
    return FALSE;

  if (! append_type (info, method_type)
      || ! append_type (info, " /* ")
      || ! append_type (info, physname)
      || ! append_type (info, " "))
    return FALSE;
  if (context || voffset != 0)
    {
      char ab[20];

      if (context)
	{
	  if (! append_type (info, "context ")
	      || ! append_type (info, context_type)
	      || ! append_type (info, " "))
	    return FALSE;
	}
      print_vma (voffset, ab, TRUE, FALSE);
      if (! append_type (info, "voffset ")
	  || ! append_type (info, ab))
	return FALSE;
    }

  return (append_type (info, " */;\n")
	  && indent_type (info));
}