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
struct error_info {char const* name; int value; char const* msg; } ;

/* Variables and functions */
 char const** error_names ; 
 struct error_info* error_table ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (char const**,int /*<<< orphan*/ ,int) ; 
 int num_error_names ; 
 char const** sys_errlist ; 
 int sys_nerr ; 

__attribute__((used)) static void
init_error_tables (void)
{
  const struct error_info *eip;
  int nbytes;

  /* If we haven't already scanned the error_table once to find the maximum
     errno value, then go find it now. */

  if (num_error_names == 0)
    {
      for (eip = error_table; eip -> name != NULL; eip++)
	{
	  if (eip -> value >= num_error_names)
	    {
	      num_error_names = eip -> value + 1;
	    }
	}
    }

  /* Now attempt to allocate the error_names table, zero it out, and then
     initialize it from the statically initialized error_table. */

  if (error_names == NULL)
    {
      nbytes = num_error_names * sizeof (char *);
      if ((error_names = (const char **) malloc (nbytes)) != NULL)
	{
	  memset (error_names, 0, nbytes);
	  for (eip = error_table; eip -> name != NULL; eip++)
	    {
	      error_names[eip -> value] = eip -> name;
	    }
	}
    }

#ifndef HAVE_SYS_ERRLIST

  /* Now attempt to allocate the sys_errlist table, zero it out, and then
     initialize it from the statically initialized error_table. */

  if (sys_errlist == NULL)
    {
      nbytes = num_error_names * sizeof (char *);
      if ((sys_errlist = (const char **) malloc (nbytes)) != NULL)
	{
	  memset (sys_errlist, 0, nbytes);
	  sys_nerr = num_error_names;
	  for (eip = error_table; eip -> name != NULL; eip++)
	    {
	      sys_errlist[eip -> value] = eip -> msg;
	    }
	}
    }

#endif

}