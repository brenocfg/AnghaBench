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
typedef  int bfd_boolean ;
struct TYPE_2__ {char const* type; } ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 scalar_t__ append_type (struct pr_handle*,char const*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  prepend_type (struct pr_handle*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ xmalloc (scalar_t__) ; 

__attribute__((used)) static bfd_boolean
substitute_type (struct pr_handle *info, const char *s)
{
  char *u;

  assert (info->stack != NULL);

  u = strchr (info->stack->type, '|');
  if (u != NULL)
    {
      char *n;

      n = (char *) xmalloc (strlen (info->stack->type) + strlen (s));

      memcpy (n, info->stack->type, u - info->stack->type);
      strcpy (n + (u - info->stack->type), s);
      strcat (n, u + 1);

      free (info->stack->type);
      info->stack->type = n;

      return TRUE;
    }

  if (strchr (s, '|') != NULL
      && (strchr (info->stack->type, '{') != NULL
	  || strchr (info->stack->type, '(') != NULL))
    {
      if (! prepend_type (info, "(")
	  || ! append_type (info, ")"))
	return FALSE;
    }

  if (*s == '\0')
    return TRUE;

  return (append_type (info, " ")
	  && append_type (info, s));
}