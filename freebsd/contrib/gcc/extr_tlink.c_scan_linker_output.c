#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* key; int tweaking; TYPE_4__* file; scalar_t__ tweaked; } ;
typedef  TYPE_1__ symbol ;
struct TYPE_7__ {char* mangled; } ;
typedef  TYPE_2__ demangled ;
struct TYPE_8__ {char* key; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ISSPACE (unsigned char) ; 
 int /*<<< orphan*/  USER_LABEL_PREFIX ; 
 char* _ (char*) ; 
 TYPE_2__* demangled_hash_lookup (char*,int) ; 
 int /*<<< orphan*/  error (char*,char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_push (TYPE_4__*) ; 
 int /*<<< orphan*/ * file_stack ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 
 scalar_t__ strstr (char const*,char*) ; 
 TYPE_1__* symbol_hash_lookup (char*,int) ; 
 int /*<<< orphan*/  temporary_firstobj ; 
 int /*<<< orphan*/  temporary_obstack ; 
 char* tfgets (int /*<<< orphan*/ *) ; 
 int tlink_verbose ; 

__attribute__((used)) static int
scan_linker_output (const char *fname)
{
  FILE *stream = fopen (fname, "r");
  char *line;
  int skip_next_in_line = 0;

  while ((line = tfgets (stream)) != NULL)
    {
      char *p = line, *q;
      symbol *sym;
      int end;
      int ok = 0;

      /* On darwin9, we might have to skip " in " lines as well.  */
      if (skip_next_in_line
	  && strstr (p, " in "))
	  continue;
      skip_next_in_line = 0;

      while (*p && ISSPACE ((unsigned char) *p))
	++p;

      if (! *p)
	continue;

      for (q = p; *q && ! ISSPACE ((unsigned char) *q); ++q)
	;

      /* Try the first word on the line.  */
      if (*p == '.')
	++p;
      if (!strncmp (p, USER_LABEL_PREFIX, strlen (USER_LABEL_PREFIX)))
	p += strlen (USER_LABEL_PREFIX);

      end = ! *q;
      *q = 0;
      sym = symbol_hash_lookup (p, false);

      /* Some SVR4 linkers produce messages like
	 ld: 0711-317 ERROR: Undefined symbol: .g__t3foo1Zi
	 */
      if (! sym && ! end && strstr (q + 1, "Undefined symbol: "))
	{
	  char *p = strrchr (q + 1, ' ');
	  p++;
	  if (*p == '.')
	    p++;
	  if (!strncmp (p, USER_LABEL_PREFIX, strlen (USER_LABEL_PREFIX)))
	    p += strlen (USER_LABEL_PREFIX);
	  sym = symbol_hash_lookup (p, false);
	}

      if (! sym && ! end)
	/* Try a mangled name in quotes.  */
	{
	  const char *oldq = q + 1;
	  demangled *dem = 0;
	  q = 0;

	  /* On darwin9, we look for "foo" referenced from:\n\(.* in .*\n\)*  */
	  if (strcmp (oldq, "referenced from:") == 0)
	    {
	      /* We have to remember that we found a symbol to tweak.  */
	      ok = 1;

	      /* We actually want to start from the first word on the
		 line.  */
	      oldq = p;

	      /* Since the format is multiline, we have to skip
		 following lines with " in ".  */
	      skip_next_in_line = 1;
	    }

	  /* First try `GNU style'.  */
	  p = strchr (oldq, '`');
	  if (p)
	    p++, q = strchr (p, '\'');
	  /* Then try "double quotes".  */
	  else if (p = strchr (oldq, '"'), p)
	    p++, q = strchr (p, '"');
	  else {
	    /* Then try entire line.  */
	    q = strchr (oldq, 0);
	    if (q != oldq)
	      p = (char *)oldq;
	  }

	  if (p)
	    {
	      /* Don't let the strstr's below see the demangled name; we
		 might get spurious matches.  */
	      p[-1] = '\0';

	      /* powerpc64-linux references .foo when calling function foo.  */
	      if (*p == '.')
		p++;
	    }

	  /* We need to check for certain error keywords here, or we would
	     mistakenly use GNU ld's "In function `foo':" message.  */
	  if (q && (ok
		    || strstr (oldq, "ndefined")
		    || strstr (oldq, "nresolved")
		    || strstr (oldq, "nsatisfied")
		    || strstr (oldq, "ultiple")))
	    {
	      *q = 0;
	      dem = demangled_hash_lookup (p, false);
	      if (dem)
		sym = symbol_hash_lookup (dem->mangled, false);
	      else
		{
		  if (!strncmp (p, USER_LABEL_PREFIX,
				strlen (USER_LABEL_PREFIX)))
		    p += strlen (USER_LABEL_PREFIX);
		  sym = symbol_hash_lookup (p, false);
		}
	    }
	}

      if (sym && sym->tweaked)
	{
	  error ("'%s' was assigned to '%s', but was not defined "
		 "during recompilation, or vice versa", 
		 sym->key, sym->file->key);
	  fclose (stream);
	  return 0;
	}
      if (sym && !sym->tweaking)
	{
	  if (tlink_verbose >= 2)
	    fprintf (stderr, _("collect: tweaking %s in %s\n"),
		     sym->key, sym->file->key);
	  sym->tweaking = 1;
	  file_push (sym->file);
	}

      obstack_free (&temporary_obstack, temporary_firstobj);
    }

  fclose (stream);
  return (file_stack != NULL);
}