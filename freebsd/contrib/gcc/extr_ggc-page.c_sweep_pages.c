#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t num_free_objects; scalar_t__ context_depth; struct TYPE_6__* next; struct TYPE_6__* prev; } ;
typedef  TYPE_1__ page_entry ;
struct TYPE_7__ {size_t allocated; scalar_t__ context_depth; TYPE_1__** pages; TYPE_1__** page_tails; } ;

/* Variables and functions */
 TYPE_5__ G ; 
 unsigned int NUM_ORDERS ; 
 size_t OBJECTS_IN_PAGE (TYPE_1__*) ; 
 size_t OBJECT_SIZE (unsigned int) ; 
 int /*<<< orphan*/  free_page (TYPE_1__*) ; 
 int /*<<< orphan*/  ggc_recalculate_in_use_p (TYPE_1__*) ; 

__attribute__((used)) static void
sweep_pages (void)
{
  unsigned order;

  for (order = 2; order < NUM_ORDERS; order++)
    {
      /* The last page-entry to consider, regardless of entries
	 placed at the end of the list.  */
      page_entry * const last = G.page_tails[order];

      size_t num_objects;
      size_t live_objects;
      page_entry *p, *previous;
      int done;

      p = G.pages[order];
      if (p == NULL)
	continue;

      previous = NULL;
      do
	{
	  page_entry *next = p->next;

	  /* Loop until all entries have been examined.  */
	  done = (p == last);

	  num_objects = OBJECTS_IN_PAGE (p);

	  /* Add all live objects on this page to the count of
             allocated memory.  */
	  live_objects = num_objects - p->num_free_objects;

	  G.allocated += OBJECT_SIZE (order) * live_objects;

	  /* Only objects on pages in the topmost context should get
	     collected.  */
	  if (p->context_depth < G.context_depth)
	    ;

	  /* Remove the page if it's empty.  */
	  else if (live_objects == 0)
	    {
	      /* If P was the first page in the list, then NEXT
		 becomes the new first page in the list, otherwise
		 splice P out of the forward pointers.  */
	      if (! previous)
		G.pages[order] = next;
	      else
		previous->next = next;
	    
	      /* Splice P out of the back pointers too.  */
	      if (next)
		next->prev = previous;

	      /* Are we removing the last element?  */
	      if (p == G.page_tails[order])
		G.page_tails[order] = previous;
	      free_page (p);
	      p = previous;
	    }

	  /* If the page is full, move it to the end.  */
	  else if (p->num_free_objects == 0)
	    {
	      /* Don't move it if it's already at the end.  */
	      if (p != G.page_tails[order])
		{
		  /* Move p to the end of the list.  */
		  p->next = NULL;
		  p->prev = G.page_tails[order];
		  G.page_tails[order]->next = p;

		  /* Update the tail pointer...  */
		  G.page_tails[order] = p;

		  /* ... and the head pointer, if necessary.  */
		  if (! previous)
		    G.pages[order] = next;
		  else
		    previous->next = next;

		  /* And update the backpointer in NEXT if necessary.  */
		  if (next)
		    next->prev = previous;

		  p = previous;
		}
	    }

	  /* If we've fallen through to here, it's a page in the
	     topmost context that is neither full nor empty.  Such a
	     page must precede pages at lesser context depth in the
	     list, so move it to the head.  */
	  else if (p != G.pages[order])
	    {
	      previous->next = p->next;

	      /* Update the backchain in the next node if it exists.  */
	      if (p->next)
		p->next->prev = previous;

	      /* Move P to the head of the list.  */
	      p->next = G.pages[order];
	      p->prev = NULL;
	      G.pages[order]->prev = p;

	      /* Update the head pointer.  */
	      G.pages[order] = p;

	      /* Are we moving the last element?  */
	      if (G.page_tails[order] == p)
	        G.page_tails[order] = previous;
	      p = previous;
	    }

	  previous = p;
	  p = next;
	}
      while (! done);

      /* Now, restore the in_use_p vectors for any pages from contexts
         other than the current one.  */
      for (p = G.pages[order]; p; p = p->next)
	if (p->context_depth != G.context_depth)
	  ggc_recalculate_in_use_p (p);
    }
}