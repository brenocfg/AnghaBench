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
 char TOUPPER (char) ; 
 int /*<<< orphan*/  notes ; 
 char* obstack_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obstack_grow (int /*<<< orphan*/ *,char const*,unsigned int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  symbols_case_sensitive ; 
 char* tc_canonicalize_symbol_name (char*) ; 

__attribute__((used)) static char *
save_symbol_name (const char *name)
{
  unsigned int name_length;
  char *ret;

  name_length = strlen (name) + 1;	/* +1 for \0.  */
  obstack_grow (&notes, name, name_length);
  ret = obstack_finish (&notes);

#ifdef tc_canonicalize_symbol_name
  ret = tc_canonicalize_symbol_name (ret);
#endif

  if (! symbols_case_sensitive)
    {
      char *s;

      for (s = ret; *s != '\0'; s++)
	*s = TOUPPER (*s);
    }

  return ret;
}