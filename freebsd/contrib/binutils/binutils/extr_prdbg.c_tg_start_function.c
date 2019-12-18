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
struct pr_handle {char* (* demangler ) (int /*<<< orphan*/ ,char const*,int) ;int parameter; TYPE_1__* stack; int /*<<< orphan*/  abfd; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_2__ {char* flavor; char* method; int /*<<< orphan*/  parents; } ;

/* Variables and functions */
 int DMGL_ANSI ; 
 int DMGL_PARAMS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  append_type (struct pr_handle*,char*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 char* strstr (char*,char*) ; 
 char* stub1 (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  substitute_type (struct pr_handle*,char*) ; 

__attribute__((used)) static bfd_boolean
tg_start_function (void *p, const char *name, bfd_boolean global)
{
  struct pr_handle *info = (struct pr_handle *) p;
  char *dname;

  if (! global)
    info->stack->flavor = "static";
  else
    info->stack->flavor = NULL;

  dname = NULL;
  if (info->demangler)
    dname = info->demangler (info->abfd, name, DMGL_ANSI | DMGL_PARAMS);

  if (! substitute_type (info, dname ? dname : name))
    return FALSE;

  info->stack->method = NULL;
  if (dname != NULL)
    {
      char *sep;
      sep = strstr (dname, "::");
      if (sep)
	{
	  info->stack->method = dname;
	  *sep = 0;
	  name = sep + 2;
	}
      else
	{
	  info->stack->method = "";
	  name = dname;
	}
      sep = strchr (name, '(');
      if (sep)
	*sep = 0;
      /* Obscure functions as type_info function.  */
    }

  info->stack->parents = strdup (name);

  if (! info->stack->method && ! append_type (info, "("))
    return FALSE;

  info->parameter = 1;

  return TRUE;
}