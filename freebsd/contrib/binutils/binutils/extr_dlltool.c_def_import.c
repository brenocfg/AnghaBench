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

/* Variables and functions */
 scalar_t__ alloca (scalar_t__) ; 
 int /*<<< orphan*/  append_import (char const*,char const*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

void
def_import (const char *app_name, const char *module, const char *dllext,
	    const char *entry, int ord_val)
{
  const char *application_name;
  char *buf;

  if (entry != NULL)
    application_name = entry;
  else
    {
      if (app_name != NULL)
	application_name = app_name;
      else
	application_name = "";
    }

  if (dllext != NULL)
    {
      buf = (char *) alloca (strlen (module) + strlen (dllext) + 2);
      sprintf (buf, "%s.%s", module, dllext);
      module = buf;
    }

  append_import (application_name, module, ord_val);
}