#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int line; char* ansi_decl; TYPE_2__* hash_entry; TYPE_4__* file; scalar_t__ prototyped; int /*<<< orphan*/  is_static; scalar_t__ is_func_def; struct TYPE_10__* next_for_func; } ;
typedef  TYPE_3__ def_dec_info ;
struct TYPE_11__ {TYPE_1__* hash_entry; } ;
struct TYPE_9__ {char* symbol; } ;
struct TYPE_8__ {char const* symbol; } ;

/* Variables and functions */
 char* alloca (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,int,char*) ; 
 scalar_t__ in_system_include_dir (char const*) ; 
 scalar_t__ is_syscalls_file (TYPE_4__*) ; 
 int /*<<< orphan*/  notice (char*,char*,...) ; 
 char* pname ; 
 int /*<<< orphan*/  quiet_flag ; 
 char* shortpath (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static const def_dec_info *
find_extern_def (const def_dec_info *head, const def_dec_info *user)
{
  const def_dec_info *dd_p;
  const def_dec_info *extern_def_p = NULL;
  int conflict_noted = 0;

  /* Don't act too stupid here.  Somebody may try to convert an entire system
     in one swell fwoop (rather than one program at a time, as should be done)
     and in that case, we may find that there are multiple extern definitions
     of a given function name in the entire set of source files that we are
     converting.  If however one of these definitions resides in exactly the
     same source file as the reference we are trying to satisfy then in that
     case it would be stupid for us to fail to realize that this one definition
     *must* be the precise one we are looking for.

     To make sure that we don't miss an opportunity to make this "same file"
     leap of faith, we do a prescan of the list of records relating to the
     given function name, and we look (on this first scan) *only* for a
     definition of the function which is in the same file as the reference
     we are currently trying to satisfy.  */

  for (dd_p = head; dd_p; dd_p = dd_p->next_for_func)
    if (dd_p->is_func_def && !dd_p->is_static && dd_p->file == user->file)
      return dd_p;

  /* Now, since we have not found a definition in the same file as the
     reference, we scan the list again and consider all possibilities from
     all files.  Here we may get conflicts with the things listed in the
     SYSCALLS.c.X file, but if that happens it only means that the source
     code being converted contains its own definition of a function which
     could have been supplied by libc.a.  In such cases, we should avoid
     issuing the normal warning, and defer to the definition given in the
     user's own code.  */

  for (dd_p = head; dd_p; dd_p = dd_p->next_for_func)
    if (dd_p->is_func_def && !dd_p->is_static)
      {
	if (!extern_def_p)	/* Previous definition? */
	  extern_def_p = dd_p;	/* Remember the first definition found.  */
	else
	  {
	    /* Ignore definition just found if it came from SYSCALLS.c.X.  */

	    if (is_syscalls_file (dd_p->file))
	      continue;

	    /* Quietly replace the definition previously found with the one
	       just found if the previous one was from SYSCALLS.c.X.  */

	    if (is_syscalls_file (extern_def_p->file))
	      {
	        extern_def_p = dd_p;
	        continue;
	      }

	    /* If we get here, then there is a conflict between two function
	       declarations for the same function, both of which came from the
	       user's own code.  */

	    if (!conflict_noted)	/* first time we noticed? */
	      {
		conflict_noted = 1;
		notice ("%s: conflicting extern definitions of '%s'\n",
			pname, head->hash_entry->symbol);
		if (!quiet_flag)
		  {
		    notice ("%s: declarations of '%s' will not be converted\n",
			    pname, head->hash_entry->symbol);
		    notice ("%s: conflict list for '%s' follows:\n",
			    pname, head->hash_entry->symbol);
		    fprintf (stderr, "%s:     %s(%d): %s\n",
			     pname,
			     shortpath (NULL, extern_def_p->file->hash_entry->symbol),
			     extern_def_p->line, extern_def_p->ansi_decl);
		  }
	      }
	    if (!quiet_flag)
	      fprintf (stderr, "%s:     %s(%d): %s\n",
		       pname,
		       shortpath (NULL, dd_p->file->hash_entry->symbol),
		       dd_p->line, dd_p->ansi_decl);
	  }
      }

  /* We want to err on the side of caution, so if we found multiple conflicting
     definitions for the same function, treat this as being that same as if we
     had found no definitions (i.e. return NULL).  */

  if (conflict_noted)
    return NULL;

  if (!extern_def_p)
    {
      /* We have no definitions for this function so do the next best thing.
	 Search for an extern declaration already in prototype form.  */

      for (dd_p = head; dd_p; dd_p = dd_p->next_for_func)
	if (!dd_p->is_func_def && !dd_p->is_static && dd_p->prototyped)
	  {
	    extern_def_p = dd_p;	/* save a pointer to the definition */
	    if (!quiet_flag)
	      notice ("%s: warning: using formals list from %s(%d) for function '%s'\n",
		      pname,
		      shortpath (NULL, dd_p->file->hash_entry->symbol),
		      dd_p->line, dd_p->hash_entry->symbol);
	    break;
	  }

      /* Gripe about unprototyped function declarations that we found no
	 corresponding definition (or other source of prototype information)
	 for.

	 Gripe even if the unprototyped declaration we are worried about
	 exists in a file in one of the "system" include directories.  We
	 can gripe about these because we should have at least found a
	 corresponding (pseudo) definition in the SYSCALLS.c.X file.  If we
	 didn't, then that means that the SYSCALLS.c.X file is missing some
	 needed prototypes for this particular system.  That is worth telling
	 the user about!  */

      if (!extern_def_p)
	{
	  const char *file = user->file->hash_entry->symbol;

	  if (!quiet_flag)
	    if (in_system_include_dir (file))
	      {
		/* Why copy this string into `needed' at all?
		   Why not just use user->ansi_decl without copying?  */
		char *needed = alloca (strlen (user->ansi_decl) + 1);
	        char *p;

	        strcpy (needed, user->ansi_decl);
	        p = strstr (needed, user->hash_entry->symbol)
	            + strlen (user->hash_entry->symbol) + 2;
		/* Avoid having ??? in the string.  */
		*p++ = '?';
		*p++ = '?';
		*p++ = '?';
	        strcpy (p, ");");

	        notice ("%s: %d: '%s' used but missing from SYSCALLS\n",
			shortpath (NULL, file), user->line,
			needed+7);	/* Don't print "extern " */
	      }
#if 0
	    else
	      notice ("%s: %d: warning: no extern definition for '%s'\n",
		      shortpath (NULL, file), user->line,
		      user->hash_entry->symbol);
#endif
	}
    }
  return extern_def_p;
}