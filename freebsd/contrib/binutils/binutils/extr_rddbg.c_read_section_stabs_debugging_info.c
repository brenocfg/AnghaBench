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
typedef  int bfd_vma ;
typedef  int bfd_size_type ;
typedef  char bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 char* bfd_errmsg (int /*<<< orphan*/ ) ; 
 int bfd_get_16 (int /*<<< orphan*/ *,char*) ; 
 int bfd_get_32 (int /*<<< orphan*/ *,char*) ; 
 int bfd_get_8 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 char* bfd_get_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bfd_get_section_by_name (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  bfd_get_section_contents (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int bfd_section_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* concat (char*,char*,char const*) ; 
 int /*<<< orphan*/  finish_stab (void*,void*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_saved_stabs () ; 
 int /*<<< orphan*/  parse_stab (void*,void*,int,int,int,char*) ; 
 int /*<<< orphan*/  save_stab (int,int,int,char*) ; 
 int /*<<< orphan*/  stab_context () ; 
 void* start_stab (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,long) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static bfd_boolean
read_section_stabs_debugging_info (bfd *abfd, asymbol **syms, long symcount,
				   void *dhandle, bfd_boolean *pfound)
{
  static struct
    {
      const char *secname;
      const char *strsecname;
    }
  names[] =
    {
      { ".stab", ".stabstr" },
      { "LC_SYMTAB.stabs", "LC_SYMTAB.stabstr" },
      { "$GDB_SYMBOLS$", "$GDB_STRINGS$" }
    };
  unsigned int i;
  void *shandle;

  *pfound = FALSE;
  shandle = NULL;

  for (i = 0; i < sizeof names / sizeof names[0]; i++)
    {
      asection *sec, *strsec;

      sec = bfd_get_section_by_name (abfd, names[i].secname);
      strsec = bfd_get_section_by_name (abfd, names[i].strsecname);
      if (sec != NULL && strsec != NULL)
	{
	  bfd_size_type stabsize, strsize;
	  bfd_byte *stabs, *strings;
	  bfd_byte *stab;
	  bfd_size_type stroff, next_stroff;

	  stabsize = bfd_section_size (abfd, sec);
	  stabs = (bfd_byte *) xmalloc (stabsize);
	  if (! bfd_get_section_contents (abfd, sec, stabs, 0, stabsize))
	    {
	      fprintf (stderr, "%s: %s: %s\n",
		       bfd_get_filename (abfd), names[i].secname,
		       bfd_errmsg (bfd_get_error ()));
	      return FALSE;
	    }

	  strsize = bfd_section_size (abfd, strsec);
	  strings = (bfd_byte *) xmalloc (strsize);
	  if (! bfd_get_section_contents (abfd, strsec, strings, 0, strsize))
	    {
	      fprintf (stderr, "%s: %s: %s\n",
		       bfd_get_filename (abfd), names[i].strsecname,
		       bfd_errmsg (bfd_get_error ()));
	      return FALSE;
	    }

	  if (shandle == NULL)
	    {
	      shandle = start_stab (dhandle, abfd, TRUE, syms, symcount);
	      if (shandle == NULL)
		return FALSE;
	    }

	  *pfound = TRUE;

	  stroff = 0;
	  next_stroff = 0;
	  for (stab = stabs; stab < stabs + stabsize; stab += 12)
	    {
	      unsigned int strx;
	      int type;
	      int other;
	      int desc;
	      bfd_vma value;

	      /* This code presumes 32 bit values.  */

	      strx = bfd_get_32 (abfd, stab);
	      type = bfd_get_8 (abfd, stab + 4);
	      other = bfd_get_8 (abfd, stab + 5);
	      desc = bfd_get_16 (abfd, stab + 6);
	      value = bfd_get_32 (abfd, stab + 8);

	      if (type == 0)
		{
		  /* Special type 0 stabs indicate the offset to the
		     next string table.  */
		  stroff = next_stroff;
		  next_stroff += value;
		}
	      else
		{
		  char *f, *s;

		  f = NULL;

		  if (stroff + strx > strsize)
		    {
		      fprintf (stderr, "%s: %s: stab entry %ld is corrupt, strx = 0x%x, type = %d\n",
			       bfd_get_filename (abfd), names[i].secname,
			       (long) (stab - stabs) / 12, strx, type);
		      continue;
		    }

		  s = (char *) strings + stroff + strx;

		  while (s[strlen (s) - 1] == '\\'
			 && stab + 12 < stabs + stabsize)
		    {
		      char *p;

		      stab += 12;
		      p = s + strlen (s) - 1;
		      *p = '\0';
		      s = concat (s,
				  ((char *) strings
				   + stroff
				   + bfd_get_32 (abfd, stab)),
				  (const char *) NULL);

		      /* We have to restore the backslash, because, if
			 the linker is hashing stabs strings, we may
			 see the same string more than once.  */
		      *p = '\\';

		      if (f != NULL)
			free (f);
		      f = s;
		    }

		  save_stab (type, desc, value, s);

		  if (! parse_stab (dhandle, shandle, type, desc, value, s))
		    {
		      stab_context ();
		      free_saved_stabs ();
		      return FALSE;
		    }

		  /* Don't free f, since I think the stabs code
		     expects strings to hang around.  This should be
		     straightened out.  FIXME.  */
		}
	    }

	  free_saved_stabs ();
	  free (stabs);

	  /* Don't free strings, since I think the stabs code expects
	     the strings to hang around.  This should be straightened
	     out.  FIXME.  */
	}
    }

  if (shandle != NULL)
    {
      if (! finish_stab (dhandle, shandle))
	return FALSE;
    }

  return TRUE;
}