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
typedef  scalar_t__ bfd_vma ;
typedef  scalar_t__ bfd_boolean ;
struct TYPE_4__ {char* type; TYPE_1__* next; } ;
struct TYPE_3__ {char* type; } ;

/* Variables and functions */
 scalar_t__ CONST_STRNEQ (char*,char*) ; 
#define  DEBUG_VISIBILITY_PRIVATE 130 
#define  DEBUG_VISIBILITY_PROTECTED 129 
#define  DEBUG_VISIBILITY_PUBLIC 128 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  append_type (struct pr_handle*,char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* pop_type (struct pr_handle*) ; 
 int /*<<< orphan*/  prepend_type (struct pr_handle*,char const*) ; 
 int /*<<< orphan*/  print_vma (scalar_t__,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  push_type (struct pr_handle*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  substitute_type (struct pr_handle*,char*) ; 
 scalar_t__ xmalloc (scalar_t__) ; 

__attribute__((used)) static bfd_boolean
pr_class_baseclass (void *p, bfd_vma bitpos, bfd_boolean virtual,
		    enum debug_visibility visibility)
{
  struct pr_handle *info = (struct pr_handle *) p;
  char *t;
  const char *prefix;
  char ab[20];
  char *s, *l, *n;

  assert (info->stack != NULL && info->stack->next != NULL);

  if (! substitute_type (info, ""))
    return FALSE;

  t = pop_type (info);
  if (t == NULL)
    return FALSE;

  if (CONST_STRNEQ (t, "class "))
    t += sizeof "class " - 1;

  /* Push it back on to take advantage of the prepend_type and
     append_type routines.  */
  if (! push_type (info, t))
    return FALSE;

  if (virtual)
    {
      if (! prepend_type (info, "virtual "))
	return FALSE;
    }

  switch (visibility)
    {
    case DEBUG_VISIBILITY_PUBLIC:
      prefix = "public ";
      break;
    case DEBUG_VISIBILITY_PROTECTED:
      prefix = "protected ";
      break;
    case DEBUG_VISIBILITY_PRIVATE:
      prefix = "private ";
      break;
    default:
      prefix = "/* unknown visibility */ ";
      break;
    }

  if (! prepend_type (info, prefix))
    return FALSE;

  if (bitpos != 0)
    {
      print_vma (bitpos, ab, TRUE, FALSE);
      if (! append_type (info, " /* bitpos ")
	  || ! append_type (info, ab)
	  || ! append_type (info, " */"))
	return FALSE;
    }

  /* Now the top of the stack is something like "public A / * bitpos
     10 * /".  The next element on the stack is something like "class
     xx { / * size 8 * /\n...".  We want to substitute the top of the
     stack in before the {.  */
  s = strchr (info->stack->next->type, '{');
  assert (s != NULL);
  --s;

  /* If there is already a ':', then we already have a baseclass, and
     we must append this one after a comma.  */
  for (l = info->stack->next->type; l != s; l++)
    if (*l == ':')
      break;
  if (! prepend_type (info, l == s ? " : " : ", "))
    return FALSE;

  t = pop_type (info);
  if (t == NULL)
    return FALSE;

  n = (char *) xmalloc (strlen (info->stack->type) + strlen (t) + 1);
  memcpy (n, info->stack->type, s - info->stack->type);
  strcpy (n + (s - info->stack->type), t);
  strcat (n, s);

  free (info->stack->type);
  info->stack->type = n;

  free (t);

  return TRUE;
}