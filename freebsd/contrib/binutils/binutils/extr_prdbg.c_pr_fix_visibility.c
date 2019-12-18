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
struct pr_handle {TYPE_1__* stack; } ;
typedef  enum debug_visibility { ____Placeholder_debug_visibility } debug_visibility ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_2__ {int visibility; char* type; } ;

/* Variables and functions */
#define  DEBUG_VISIBILITY_IGNORE 131 
#define  DEBUG_VISIBILITY_PRIVATE 130 
#define  DEBUG_VISIBILITY_PROTECTED 129 
#define  DEBUG_VISIBILITY_PUBLIC 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  append_type (struct pr_handle*,char const*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  indent_type (struct pr_handle*) ; 
 unsigned int strlen (char*) ; 

__attribute__((used)) static bfd_boolean
pr_fix_visibility (struct pr_handle *info, enum debug_visibility visibility)
{
  const char *s = NULL;
  char *t;
  unsigned int len;

  assert (info->stack != NULL);

  if (info->stack->visibility == visibility)
    return TRUE;

  switch (visibility)
    {
    case DEBUG_VISIBILITY_PUBLIC:
      s = "public";
      break;
    case DEBUG_VISIBILITY_PRIVATE:
      s = "private";
      break;
    case DEBUG_VISIBILITY_PROTECTED:
      s = "protected";
      break;
    case DEBUG_VISIBILITY_IGNORE:
      s = "/* ignore */";
      break;
    default:
      abort ();
      return FALSE;
    }

  /* Trim off a trailing space in the struct string, to make the
     output look a bit better, then stick on the visibility string.  */

  t = info->stack->type;
  len = strlen (t);
  assert (t[len - 1] == ' ');
  t[len - 1] = '\0';

  if (! append_type (info, s)
      || ! append_type (info, ":\n")
      || ! indent_type (info))
    return FALSE;

  info->stack->visibility = visibility;

  return TRUE;
}