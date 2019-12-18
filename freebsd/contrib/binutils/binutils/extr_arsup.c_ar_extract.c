#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct list {char* name; struct list* next; } ;
struct TYPE_4__ {struct TYPE_4__* archive_next; int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ bfd ;
struct TYPE_5__ {TYPE_1__* archive_head; } ;

/* Variables and functions */
 scalar_t__ FILENAME_CMP (int /*<<< orphan*/ ,char*) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  bfd_openr (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_file (TYPE_1__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  maybequit () ; 
 TYPE_2__* obfd ; 
 char* program_name ; 
 int /*<<< orphan*/  stderr ; 

void
ar_extract (struct list *list)
{
  if (!obfd)
    {
      fprintf (stderr, _("%s: no open archive\n"), program_name);
      maybequit ();
    }
  else
    {
      while (list)
	{
	  /* Find this name in the archive.  */
	  bfd *member = obfd->archive_head;
	  int found = 0;

	  while (member && !found)
	    {
	      if (FILENAME_CMP (member->filename, list->name) == 0)
		{
		  extract_file (member);
		  found = 1;
		}

	      member = member->archive_next;
	    }

	  if (!found)
	    {
	      bfd_openr (list->name, 0);
	      fprintf (stderr, _("%s: can't find module file %s\n"),
		       program_name, list->name);
	    }

	  list = list->next;
	}
    }
}