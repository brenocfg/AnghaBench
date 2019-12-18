#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char type; char* name; int /*<<< orphan*/  value; int /*<<< orphan*/  stab_desc; int /*<<< orphan*/  stab_type; } ;
typedef  TYPE_1__ symbol_info ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bfd_asymbol_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_symbol_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 char* concat (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  finish_stab (void*,void*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_saved_stabs () ; 
 int /*<<< orphan*/  parse_stab (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  save_stab (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  stab_context () ; 
 void* start_stab (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,long) ; 
 int strlen (char const*) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static bfd_boolean
read_symbol_stabs_debugging_info (bfd *abfd, asymbol **syms, long symcount,
				  void *dhandle, bfd_boolean *pfound)
{
  void *shandle;
  asymbol **ps, **symend;

  shandle = NULL;
  symend = syms + symcount;
  for (ps = syms; ps < symend; ps++)
    {
      symbol_info i;

      bfd_get_symbol_info (abfd, *ps, &i);

      if (i.type == '-')
	{
	  const char *s;
	  char *f;

	  if (shandle == NULL)
	    {
	      shandle = start_stab (dhandle, abfd, FALSE, syms, symcount);
	      if (shandle == NULL)
		return FALSE;
	    }

	  *pfound = TRUE;

	  s = i.name;
	  f = NULL;
	  while (s[strlen (s) - 1] == '\\'
		 && ps + 1 < symend)
	    {
	      char *sc, *n;

	      ++ps;
	      sc = xstrdup (s);
	      sc[strlen (sc) - 1] = '\0';
	      n = concat (sc, bfd_asymbol_name (*ps), (const char *) NULL);
	      free (sc);
	      if (f != NULL)
		free (f);
	      f = n;
	      s = n;
	    }

	  save_stab (i.stab_type, i.stab_desc, i.value, s);

	  if (! parse_stab (dhandle, shandle, i.stab_type, i.stab_desc,
			    i.value, s))
	    {
	      stab_context ();
	      free_saved_stabs ();
	      return FALSE;
	    }

	  /* Don't free f, since I think the stabs code expects
	     strings to hang around.  This should be straightened out.
	     FIXME.  */
	}
    }

  free_saved_stabs ();

  if (shandle != NULL)
    {
      if (! finish_stab (dhandle, shandle))
	return FALSE;
    }

  return TRUE;
}