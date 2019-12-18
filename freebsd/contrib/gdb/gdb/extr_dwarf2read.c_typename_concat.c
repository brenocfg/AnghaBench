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
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 char* xmalloc (scalar_t__) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static char *
typename_concat (const char *prefix, const char *suffix)
{
  if (prefix == NULL || prefix[0] == '\0')
    return xstrdup (suffix);
  else
    {
      char *retval = xmalloc (strlen (prefix) + 2 + strlen (suffix) + 1);

      strcpy (retval, prefix);
      strcat (retval, "::");
      strcat (retval, suffix);

      return retval;
    }
}