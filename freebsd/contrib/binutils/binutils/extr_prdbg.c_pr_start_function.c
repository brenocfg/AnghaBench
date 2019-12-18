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
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  indent (struct pr_handle*) ; 
 char* pop_type (struct pr_handle*) ; 
 int /*<<< orphan*/  substitute_type (struct pr_handle*,char const*) ; 

__attribute__((used)) static bfd_boolean
pr_start_function (void *p, const char *name, bfd_boolean global)
{
  struct pr_handle *info = (struct pr_handle *) p;
  char *t;

  if (! substitute_type (info, name))
    return FALSE;

  t = pop_type (info);
  if (t == NULL)
    return FALSE;

  indent (info);
  if (! global)
    fprintf (info->f, "static ");
  fprintf (info->f, "%s (", t);

  info->parameter = 1;

  return TRUE;
}