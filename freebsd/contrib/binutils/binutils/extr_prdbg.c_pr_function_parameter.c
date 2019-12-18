#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pr_handle {int parameter; int /*<<< orphan*/  f; } ;
typedef  enum debug_parm_kind { ____Placeholder_debug_parm_kind } debug_parm_kind ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int DEBUG_PARM_REFERENCE ; 
 int DEBUG_PARM_REF_REG ; 
 int DEBUG_PARM_REG ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* pop_type (struct pr_handle*) ; 
 int /*<<< orphan*/  pr_reference_type (void*) ; 
 int /*<<< orphan*/  print_vma (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  substitute_type (struct pr_handle*,char const*) ; 

__attribute__((used)) static bfd_boolean
pr_function_parameter (void *p, const char *name,
		       enum debug_parm_kind kind, bfd_vma val)
{
  struct pr_handle *info = (struct pr_handle *) p;
  char *t;
  char ab[20];

  if (kind == DEBUG_PARM_REFERENCE
      || kind == DEBUG_PARM_REF_REG)
    {
      if (! pr_reference_type (p))
	return FALSE;
    }

  if (! substitute_type (info, name))
    return FALSE;

  t = pop_type (info);
  if (t == NULL)
    return FALSE;

  if (info->parameter != 1)
    fprintf (info->f, ", ");

  if (kind == DEBUG_PARM_REG || kind == DEBUG_PARM_REF_REG)
    fprintf (info->f, "register ");

  print_vma (val, ab, TRUE, TRUE);
  fprintf (info->f, "%s /* %s */", t, ab);

  free (t);

  ++info->parameter;

  return TRUE;
}