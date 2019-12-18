#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct list {char* name; struct list* next; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_7__ {int /*<<< orphan*/ * filename; struct TYPE_7__* archive_next; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FILENAME_CMP (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
map_over_list (bfd *arch, void (*function) (bfd *, bfd *), struct list *list)
{
  bfd *head;

  if (list == NULL)
    {
      bfd *next;

      head = arch->archive_next;
      while (head != NULL)
	{
	  next = head->archive_next;
	  function (head, (bfd *) NULL);
	  head = next;
	}
    }
  else
    {
      struct list *ptr;

      /* This may appear to be a baroque way of accomplishing what we
	 want.  however we have to iterate over the filenames in order
	 to notice where a filename is requested but does not exist in
	 the archive.  Ditto mapping over each file each time -- we
	 want to hack multiple references.  */
      for (ptr = list; ptr; ptr = ptr->next)
	{
	  bfd_boolean found = FALSE;
	  bfd *prev = arch;

	  for (head = arch->archive_next; head; head = head->archive_next)
	    {
	      if (head->filename != NULL
		  && FILENAME_CMP (ptr->name, head->filename) == 0)
		{
		  found = TRUE;
		  function (head, prev);
		}
	      prev = head;
	    }
	  if (! found)
	    fprintf (stderr, _("No entry %s in archive.\n"), ptr->name);
	}
    }
}