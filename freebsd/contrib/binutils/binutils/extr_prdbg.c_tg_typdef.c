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
struct pr_handle {char* filename; int /*<<< orphan*/  f; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* pop_type (struct pr_handle*) ; 

__attribute__((used)) static bfd_boolean
tg_typdef (void *p, const char *name)
{
  struct pr_handle *info = (struct pr_handle *) p;
  char *s;

  s = pop_type (info);
  if (s == NULL)
    return FALSE;

  fprintf (info->f, "%s\t%s\t0;\"\tkind:t\ttype:%s\n", name,
	   info->filename, s);

  free (s);

  return TRUE;
}