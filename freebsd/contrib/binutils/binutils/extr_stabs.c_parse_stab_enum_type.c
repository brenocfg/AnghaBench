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
typedef  int /*<<< orphan*/  debug_type ;
typedef  char const* bfd_signed_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_TYPE_NULL ; 
 int /*<<< orphan*/  bad_stab (char const*) ; 
 int /*<<< orphan*/  debug_make_enum_type (void*,char const**,char const**) ; 
 scalar_t__ parse_number (char const**,int /*<<< orphan*/ *) ; 
 char* savestring (char const*,int) ; 
 scalar_t__ xmalloc (unsigned int) ; 
 scalar_t__ xrealloc (char const**,unsigned int) ; 

__attribute__((used)) static debug_type
parse_stab_enum_type (void *dhandle, const char **pp)
{
  const char *orig;
  const char **names;
  bfd_signed_vma *values;
  unsigned int n;
  unsigned int alloc;

  orig = *pp;

  /* FIXME: gdb checks os9k_stabs here.  */

  /* The aix4 compiler emits an extra field before the enum members;
     my guess is it's a type of some sort.  Just ignore it.  */
  if (**pp == '-')
    {
      while (**pp != ':')
	++*pp;
      ++*pp;
    }

  /* Read the value-names and their values.
     The input syntax is NAME:VALUE,NAME:VALUE, and so on.
     A semicolon or comma instead of a NAME means the end.  */
  alloc = 10;
  names = (const char **) xmalloc (alloc * sizeof *names);
  values = (bfd_signed_vma *) xmalloc (alloc * sizeof *values);
  n = 0;
  while (**pp != '\0' && **pp != ';' && **pp != ',')
    {
      const char *p;
      char *name;
      bfd_signed_vma val;

      p = *pp;
      while (*p != ':')
	++p;

      name = savestring (*pp, p - *pp);

      *pp = p + 1;
      val = (bfd_signed_vma) parse_number (pp, (bfd_boolean *) NULL);
      if (**pp != ',')
	{
	  bad_stab (orig);
	  return DEBUG_TYPE_NULL;
	}
      ++*pp;

      if (n + 1 >= alloc)
	{
	  alloc += 10;
	  names = ((const char **)
		   xrealloc (names, alloc * sizeof *names));
	  values = ((bfd_signed_vma *)
		    xrealloc (values, alloc * sizeof *values));
	}

      names[n] = name;
      values[n] = val;
      ++n;
    }

  names[n] = NULL;
  values[n] = 0;

  if (**pp == ';')
    ++*pp;

  return debug_make_enum_type (dhandle, names, values);
}