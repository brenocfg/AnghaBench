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
struct subfile {scalar_t__ language; struct subfile* next; int /*<<< orphan*/ * name; int /*<<< orphan*/ * debugformat; int /*<<< orphan*/ * line_vector; int /*<<< orphan*/ * dirname; } ;
typedef  enum language { ____Placeholder_language } language ;

/* Variables and functions */
 scalar_t__ FILENAME_CMP (int /*<<< orphan*/ *,char*) ; 
 struct subfile* current_subfile ; 
 void* deduce_language_from_filename (int /*<<< orphan*/ *) ; 
 scalar_t__ language_c ; 
 int language_cplus ; 
 int language_fortran ; 
 scalar_t__ language_unknown ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * savestring (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 struct subfile* subfiles ; 
 scalar_t__ xmalloc (int) ; 

void
start_subfile (char *name, char *dirname)
{
  struct subfile *subfile;

  /* See if this subfile is already known as a subfile of the current
     main source file.  */

  for (subfile = subfiles; subfile; subfile = subfile->next)
    {
      if (FILENAME_CMP (subfile->name, name) == 0)
	{
	  current_subfile = subfile;
	  return;
	}
    }

  /* This subfile is not known.  Add an entry for it. Make an entry
     for this subfile in the list of all subfiles of the current main
     source file.  */

  subfile = (struct subfile *) xmalloc (sizeof (struct subfile));
  memset ((char *) subfile, 0, sizeof (struct subfile));
  subfile->next = subfiles;
  subfiles = subfile;
  current_subfile = subfile;

  /* Save its name and compilation directory name */
  subfile->name = (name == NULL) ? NULL : savestring (name, strlen (name));
  subfile->dirname =
    (dirname == NULL) ? NULL : savestring (dirname, strlen (dirname));

  /* Initialize line-number recording for this subfile.  */
  subfile->line_vector = NULL;

  /* Default the source language to whatever can be deduced from the
     filename.  If nothing can be deduced (such as for a C/C++ include
     file with a ".h" extension), then inherit whatever language the
     previous subfile had.  This kludgery is necessary because there
     is no standard way in some object formats to record the source
     language.  Also, when symtabs are allocated we try to deduce a
     language then as well, but it is too late for us to use that
     information while reading symbols, since symtabs aren't allocated
     until after all the symbols have been processed for a given
     source file. */

  subfile->language = deduce_language_from_filename (subfile->name);
  if (subfile->language == language_unknown &&
      subfile->next != NULL)
    {
      subfile->language = subfile->next->language;
    }

  /* Initialize the debug format string to NULL.  We may supply it
     later via a call to record_debugformat. */
  subfile->debugformat = NULL;

  /* If the filename of this subfile ends in .C, then change the
     language of any pending subfiles from C to C++.  We also accept
     any other C++ suffixes accepted by deduce_language_from_filename.  */
  /* Likewise for f2c.  */

  if (subfile->name)
    {
      struct subfile *s;
      enum language sublang = deduce_language_from_filename (subfile->name);

      if (sublang == language_cplus || sublang == language_fortran)
	for (s = subfiles; s != NULL; s = s->next)
	  if (s->language == language_c)
	    s->language = sublang;
    }

  /* And patch up this file if necessary.  */
  if (subfile->language == language_c
      && subfile->next != NULL
      && (subfile->next->language == language_cplus
	  || subfile->next->language == language_fortran))
    {
      subfile->language = subfile->next->language;
    }
}