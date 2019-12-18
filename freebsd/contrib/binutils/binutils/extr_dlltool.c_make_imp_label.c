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
 char const* ASM_PREFIX (char const*) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 char* xmalloc (int) ; 

__attribute__((used)) static char *
make_imp_label (const char *prefix, const char *name)
{
  int len;
  char *copy;

  if (name[0] == '@')
    {
      len = strlen (prefix) + strlen (name);
      copy = xmalloc (len + 1);
      strcpy (copy, prefix);
      strcat (copy, name);
    }
  else
    {
      len = strlen (ASM_PREFIX (name)) + strlen (prefix) + strlen (name);
      copy = xmalloc (len + 1);
      strcpy (copy, prefix);
      strcat (copy, ASM_PREFIX (name));
      strcat (copy, name);
    }
  return copy;
}