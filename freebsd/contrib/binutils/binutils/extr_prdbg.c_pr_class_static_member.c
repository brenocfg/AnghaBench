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
struct pr_handle {int dummy; } ;
typedef  enum debug_visibility { ____Placeholder_debug_visibility } debug_visibility ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  append_type (struct pr_handle*,char const*) ; 
 int /*<<< orphan*/  indent_type (struct pr_handle*) ; 
 char* pop_type (struct pr_handle*) ; 
 int /*<<< orphan*/  pr_fix_visibility (struct pr_handle*,int) ; 
 int /*<<< orphan*/  prepend_type (struct pr_handle*,char*) ; 
 int /*<<< orphan*/  substitute_type (struct pr_handle*,char const*) ; 

__attribute__((used)) static bfd_boolean
pr_class_static_member (void *p, const char *name, const char *physname,
			enum debug_visibility visibility)
{
  struct pr_handle *info = (struct pr_handle *) p;
  char *t;

  if (! substitute_type (info, name))
    return FALSE;

  if (! prepend_type (info, "static ")
      || ! append_type (info, "; /* ")
      || ! append_type (info, physname)
      || ! append_type (info, " */\n")
      || ! indent_type (info))
    return FALSE;

  t = pop_type (info);
  if (t == NULL)
    return FALSE;

  if (! pr_fix_visibility (info, visibility))
    return FALSE;

  return append_type (info, t);
}