#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct subfile {char* dirname; char* name; scalar_t__ language; TYPE_1__* next; } ;
struct TYPE_2__ {scalar_t__ language; } ;

/* Variables and functions */
 scalar_t__ deduce_language_from_filename (char*) ; 
 scalar_t__ language_unknown ; 
 char* last_source_file ; 
 char* savestring (char*,int) ; 
 int strlen (char*) ; 

void
patch_subfile_names (struct subfile *subfile, char *name)
{
  if (subfile != NULL && subfile->dirname == NULL && subfile->name != NULL
      && subfile->name[strlen (subfile->name) - 1] == '/')
    {
      subfile->dirname = subfile->name;
      subfile->name = savestring (name, strlen (name));
      last_source_file = name;

      /* Default the source language to whatever can be deduced from
         the filename.  If nothing can be deduced (such as for a C/C++
         include file with a ".h" extension), then inherit whatever
         language the previous subfile had.  This kludgery is
         necessary because there is no standard way in some object
         formats to record the source language.  Also, when symtabs
         are allocated we try to deduce a language then as well, but
         it is too late for us to use that information while reading
         symbols, since symtabs aren't allocated until after all the
         symbols have been processed for a given source file. */

      subfile->language = deduce_language_from_filename (subfile->name);
      if (subfile->language == language_unknown &&
	  subfile->next != NULL)
	{
	  subfile->language = subfile->next->language;
	}
    }
}