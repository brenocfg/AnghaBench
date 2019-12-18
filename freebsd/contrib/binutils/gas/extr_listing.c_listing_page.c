#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ edict; char* edict_arg; struct TYPE_3__* next; } ;
typedef  TYPE_1__ list_info_type ;

/* Variables and functions */
 scalar_t__ EDICT_SBTTL ; 
 scalar_t__ EDICT_TITLE ; 
 char* LISTING_HEADER ; 
 scalar_t__ eject ; 
 char* fn ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  list_file ; 
 unsigned int on_page ; 
 int page ; 
 scalar_t__ paper_height ; 
 char* subtitle ; 
 char* title ; 

__attribute__((used)) static void
listing_page (list_info_type *list)
{
  /* Grope around, see if we can see a title or subtitle edict coming up
     soon.  (we look down 10 lines of the page and see if it's there)  */
  if ((eject || (on_page >= (unsigned int) paper_height))
      && paper_height != 0)
    {
      unsigned int c = 10;
      int had_title = 0;
      int had_subtitle = 0;

      page++;

      while (c != 0 && list)
	{
	  if (list->edict == EDICT_SBTTL && !had_subtitle)
	    {
	      had_subtitle = 1;
	      subtitle = list->edict_arg;
	    }
	  if (list->edict == EDICT_TITLE && !had_title)
	    {
	      had_title = 1;
	      title = list->edict_arg;
	    }
	  list = list->next;
	  c--;
	}

      if (page > 1)
	{
	  fprintf (list_file, "\f");
	}

      fprintf (list_file, "%s %s \t\t\tpage %d\n", LISTING_HEADER, fn, page);
      fprintf (list_file, "%s\n", title);
      fprintf (list_file, "%s\n", subtitle);
      on_page = 3;
      eject = 0;
    }
}