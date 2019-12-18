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
struct TYPE_4__ {struct TYPE_4__* archive_next; } ;
typedef  TYPE_1__ bfd ;
struct TYPE_5__ {TYPE_1__* archive_head; } ;

/* Variables and functions */
 char* _ (char*) ; 
 TYPE_1__* bfd_openr (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  maybequit () ; 
 TYPE_2__* obfd ; 
 char* program_name ; 
 int /*<<< orphan*/  stderr ; 

void
ar_addmod (struct list *list)
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
	  bfd *abfd = bfd_openr (list->name, NULL);

	  if (!abfd)
	    {
	      fprintf (stderr, _("%s: can't open file %s\n"),
		       program_name, list->name);
	      maybequit ();
	    }
	  else
	    {
	      abfd->archive_next = obfd->archive_head;
	      obfd->archive_head = abfd;
	    }
	  list = list->next;
	}
    }
}