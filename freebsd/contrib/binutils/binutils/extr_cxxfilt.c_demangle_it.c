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
 char* cplus_demangle (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flags ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 scalar_t__ strip_underscore ; 

__attribute__((used)) static void
demangle_it (char *mangled_name)
{
  char *result;
  unsigned int skip_first = 0;

  /* _ and $ are sometimes found at the start of function names
     in assembler sources in order to distinguish them from other
     names (eg register names).  So skip them here.  */
  if (mangled_name[0] == '.' || mangled_name[0] == '$')
    ++skip_first;
  if (strip_underscore && mangled_name[skip_first] == '_')
    ++skip_first;

  result = cplus_demangle (mangled_name + skip_first, flags);

  if (result == NULL)
    printf ("%s",mangled_name);
  else
    {
      if (mangled_name[0] == '.')
	putchar ('.');
      printf ("%s",result);
      free (result);
    }
}