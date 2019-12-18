#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct list {char* name; struct list* next; } ;
struct TYPE_3__ {struct TYPE_3__* archive_next; int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ bfd ;
struct TYPE_4__ {TYPE_1__* archive_head; } ;

/* Variables and functions */
 scalar_t__ FILENAME_CMP (int /*<<< orphan*/ ,char*) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  maybequit () ; 
 TYPE_2__* obfd ; 
 char* program_name ; 
 int /*<<< orphan*/  stderr ; 

void
ar_delete (struct list *list)
{
  if (!obfd)
    {
      fprintf (stderr, _("%s: no open output archive\n"), program_name);
      maybequit ();
    }
  else
    {
      while (list)
	{
	  /* Find this name in the archive.  */
	  bfd *member = obfd->archive_head;
	  bfd **prev = &(obfd->archive_head);
	  int found = 0;

	  while (member)
	    {
	      if (FILENAME_CMP(member->filename, list->name) == 0)
		{
		  *prev = member->archive_next;
		  found = 1;
		}
	      else
		prev = &(member->archive_next);

	      member = member->archive_next;
	    }

	  if (!found)
	    {
	      fprintf (stderr, _("%s: can't find module file %s\n"),
		       program_name, list->name);
	      maybequit ();
	    }

	  list = list->next;
	}
    }
}