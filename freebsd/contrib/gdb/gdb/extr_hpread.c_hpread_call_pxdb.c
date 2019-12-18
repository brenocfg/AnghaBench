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
 char const* PXDB_SVR4 ; 
 scalar_t__ file_exists (char const*) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int system (char*) ; 
 int /*<<< orphan*/  warning (char*,...) ; 
 char* xmalloc (scalar_t__) ; 

__attribute__((used)) static int
hpread_call_pxdb (const char *file_name)
{
  char *p;
  int status;
  int retval;

  if (file_exists (PXDB_SVR4))
    {
      p = xmalloc (strlen (PXDB_SVR4) + strlen (file_name) + 2);
      strcpy (p, PXDB_SVR4);
      strcat (p, " ");
      strcat (p, file_name);

      warning ("File not processed by pxdb--about to process now.\n");
      status = system (p);

      retval = (status == 0);
    }
  else
    {
      warning ("pxdb not found at standard location: /opt/langtools/bin\ngdb will not be able to debug %s.\nPlease install pxdb at the above location and then restart gdb.\nYou can also run pxdb on %s with the command\n\"pxdb %s\" and then restart gdb.", file_name, file_name, file_name);

      retval = 0;
    }
  return retval;
}