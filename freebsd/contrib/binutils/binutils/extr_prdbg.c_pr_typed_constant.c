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
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  indent (struct pr_handle*) ; 
 char* pop_type (struct pr_handle*) ; 
 int /*<<< orphan*/  print_vma (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
pr_typed_constant (void *p, const char *name, bfd_vma val)
{
  struct pr_handle *info = (struct pr_handle *) p;
  char *t;
  char ab[20];

  t = pop_type (info);
  if (t == NULL)
    return FALSE;

  indent (info);
  print_vma (val, ab, FALSE, FALSE);
  fprintf (info->f, "const %s %s = %s;\n", t, name, ab);

  free (t);

  return TRUE;
}