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
struct pr_handle {int /*<<< orphan*/  f; } ;
typedef  enum debug_var_kind { ____Placeholder_debug_var_kind } debug_var_kind ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
#define  DEBUG_LOCAL_STATIC 130 
#define  DEBUG_REGISTER 129 
#define  DEBUG_STATIC 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  indent (struct pr_handle*) ; 
 char* pop_type (struct pr_handle*) ; 
 int /*<<< orphan*/  print_vma (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  substitute_type (struct pr_handle*,char const*) ; 

__attribute__((used)) static bfd_boolean
pr_variable (void *p, const char *name, enum debug_var_kind kind,
	     bfd_vma val)
{
  struct pr_handle *info = (struct pr_handle *) p;
  char *t;
  char ab[20];

  if (! substitute_type (info, name))
    return FALSE;

  t = pop_type (info);
  if (t == NULL)
    return FALSE;

  indent (info);
  switch (kind)
    {
    case DEBUG_STATIC:
    case DEBUG_LOCAL_STATIC:
      fprintf (info->f, "static ");
      break;
    case DEBUG_REGISTER:
      fprintf (info->f, "register ");
      break;
    default:
      break;
    }
  print_vma (val, ab, TRUE, TRUE);
  fprintf (info->f, "%s /* %s */;\n", t, ab);

  free (t);

  return TRUE;
}