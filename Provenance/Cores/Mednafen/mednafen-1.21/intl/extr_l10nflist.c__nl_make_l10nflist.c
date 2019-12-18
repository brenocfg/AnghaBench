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
struct loaded_l10nfile {char* filename; int decided; struct loaded_l10nfile** successor; struct loaded_l10nfile* next; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 scalar_t__ IS_ABSOLUTE_PATH (char const*) ; 
 int /*<<< orphan*/  PATH_SEPARATOR ; 
 int XPG_CODESET ; 
 int XPG_MODIFIER ; 
 int XPG_NORM_CODESET ; 
 int XPG_TERRITORY ; 
 int __argz_count (char const*,size_t) ; 
 char* __argz_next (char*,size_t,char*) ; 
 int /*<<< orphan*/  __argz_stringify (char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t pop (int) ; 
 char* stpcpy (char*,char const*) ; 
 int strcmp (char*,char*) ; 
 int strlen (char const*) ; 

struct loaded_l10nfile *
_nl_make_l10nflist (struct loaded_l10nfile **l10nfile_list,
		    const char *dirlist, size_t dirlist_len,
		    int mask, const char *language, const char *territory,
		    const char *codeset, const char *normalized_codeset,
		    const char *modifier,
		    const char *filename, int do_allocate)
{
  char *abs_filename;
  struct loaded_l10nfile **lastp;
  struct loaded_l10nfile *retval;
  char *cp;
  size_t dirlist_count;
  size_t entries;
  int cnt;

  /* If LANGUAGE contains an absolute directory specification, we ignore
     DIRLIST.  */
  if (IS_ABSOLUTE_PATH (language))
    dirlist_len = 0;

  /* Allocate room for the full file name.  */
  abs_filename = (char *) malloc (dirlist_len
				  + strlen (language)
				  + ((mask & XPG_TERRITORY) != 0
				     ? strlen (territory) + 1 : 0)
				  + ((mask & XPG_CODESET) != 0
				     ? strlen (codeset) + 1 : 0)
				  + ((mask & XPG_NORM_CODESET) != 0
				     ? strlen (normalized_codeset) + 1 : 0)
				  + ((mask & XPG_MODIFIER) != 0
				     ? strlen (modifier) + 1 : 0)
				  + 1 + strlen (filename) + 1);

  if (abs_filename == NULL)
    return NULL;

  /* Construct file name.  */
  cp = abs_filename;
  if (dirlist_len > 0)
    {
      memcpy (cp, dirlist, dirlist_len);
      __argz_stringify (cp, dirlist_len, PATH_SEPARATOR);
      cp += dirlist_len;
      cp[-1] = '/';
    }

  cp = stpcpy (cp, language);

  if ((mask & XPG_TERRITORY) != 0)
    {
      *cp++ = '_';
      cp = stpcpy (cp, territory);
    }
  if ((mask & XPG_CODESET) != 0)
    {
      *cp++ = '.';
      cp = stpcpy (cp, codeset);
    }
  if ((mask & XPG_NORM_CODESET) != 0)
    {
      *cp++ = '.';
      cp = stpcpy (cp, normalized_codeset);
    }
  if ((mask & XPG_MODIFIER) != 0)
    {
      *cp++ = '@';
      cp = stpcpy (cp, modifier);
    }

  *cp++ = '/';
  stpcpy (cp, filename);

  /* Look in list of already loaded domains whether it is already
     available.  */
  lastp = l10nfile_list;
  for (retval = *l10nfile_list; retval != NULL; retval = retval->next)
    if (retval->filename != NULL)
      {
	int compare = strcmp (retval->filename, abs_filename);
	if (compare == 0)
	  /* We found it!  */
	  break;
	if (compare < 0)
	  {
	    /* It's not in the list.  */
	    retval = NULL;
	    break;
	  }

	lastp = &retval->next;
      }

  if (retval != NULL || do_allocate == 0)
    {
      free (abs_filename);
      return retval;
    }

  dirlist_count = (dirlist_len > 0 ? __argz_count (dirlist, dirlist_len) : 1);

  /* Allocate a new loaded_l10nfile.  */
  retval =
    (struct loaded_l10nfile *)
    malloc (sizeof (*retval)
	    + (((dirlist_count << pop (mask)) + (dirlist_count > 1 ? 1 : 0))
	       * sizeof (struct loaded_l10nfile *)));
  if (retval == NULL)
    {
      free (abs_filename);
      return NULL;
    }

  retval->filename = abs_filename;

  /* We set retval->data to NULL here; it is filled in later.
     Setting retval->decided to 1 here means that retval does not
     correspond to a real file (dirlist_count > 1) or is not worth
     looking up (if an unnormalized codeset was specified).  */
  retval->decided = (dirlist_count > 1
		     || ((mask & XPG_CODESET) != 0
			 && (mask & XPG_NORM_CODESET) != 0));
  retval->data = NULL;

  retval->next = *lastp;
  *lastp = retval;

  entries = 0;
  /* Recurse to fill the inheritance list of RETVAL.
     If the DIRLIST is a real list (i.e. DIRLIST_COUNT > 1), the RETVAL
     entry does not correspond to a real file; retval->filename contains
     colons.  In this case we loop across all elements of DIRLIST and
     across all bit patterns dominated by MASK.
     If the DIRLIST is a single directory or entirely redundant (i.e.
     DIRLIST_COUNT == 1), we loop across all bit patterns dominated by
     MASK, excluding MASK itself.
     In either case, we loop down from MASK to 0.  This has the effect
     that the extra bits in the locale name are dropped in this order:
     first the modifier, then the territory, then the codeset, then the
     normalized_codeset.  */
  for (cnt = dirlist_count > 1 ? mask : mask - 1; cnt >= 0; --cnt)
    if ((cnt & ~mask) == 0
	&& !((cnt & XPG_CODESET) != 0 && (cnt & XPG_NORM_CODESET) != 0))
      {
	if (dirlist_count > 1)
	  {
	    /* Iterate over all elements of the DIRLIST.  */
	    char *dir = NULL;

	    while ((dir = __argz_next ((char *) dirlist, dirlist_len, dir))
		   != NULL)
	      retval->successor[entries++]
		= _nl_make_l10nflist (l10nfile_list, dir, strlen (dir) + 1,
				      cnt, language, territory, codeset,
				      normalized_codeset, modifier, filename,
				      1);
	  }
	else
	  retval->successor[entries++]
	    = _nl_make_l10nflist (l10nfile_list, dirlist, dirlist_len,
				  cnt, language, territory, codeset,
				  normalized_codeset, modifier, filename, 1);
      }
  retval->successor[entries] = NULL;

  return retval;
}