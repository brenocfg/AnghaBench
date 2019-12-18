#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ in_use; struct TYPE_7__* next; TYPE_3__* allocation; scalar_t__ alloc_size; } ;
typedef  TYPE_2__ page_group ;
struct TYPE_8__ {char* page; size_t bytes; struct TYPE_8__* next; TYPE_1__* group; } ;
typedef  TYPE_3__ page_entry ;
struct TYPE_9__ {size_t bytes_mapped; TYPE_2__* page_groups; TYPE_3__* free_pages; } ;
struct TYPE_6__ {scalar_t__ in_use; } ;

/* Variables and functions */
 TYPE_5__ G ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  munmap (char*,size_t) ; 

__attribute__((used)) static void
release_pages (void)
{
#ifdef USING_MMAP
  page_entry *p, *next;
  char *start;
  size_t len;

  /* Gather up adjacent pages so they are unmapped together.  */
  p = G.free_pages;

  while (p)
    {
      start = p->page;
      next = p->next;
      len = p->bytes;
      free (p);
      p = next;

      while (p && p->page == start + len)
	{
	  next = p->next;
	  len += p->bytes;
	  free (p);
	  p = next;
	}

      munmap (start, len);
      G.bytes_mapped -= len;
    }

  G.free_pages = NULL;
#endif
#ifdef USING_MALLOC_PAGE_GROUPS
  page_entry **pp, *p;
  page_group **gp, *g;

  /* Remove all pages from free page groups from the list.  */
  pp = &G.free_pages;
  while ((p = *pp) != NULL)
    if (p->group->in_use == 0)
      {
	*pp = p->next;
	free (p);
      }
    else
      pp = &p->next;

  /* Remove all free page groups, and release the storage.  */
  gp = &G.page_groups;
  while ((g = *gp) != NULL)
    if (g->in_use == 0)
      {
	*gp = g->next;
	G.bytes_mapped -= g->alloc_size;
	free (g->allocation);
      }
    else
      gp = &g->next;
#endif
}