#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {unsigned int indx; struct TYPE_9__* prev; struct TYPE_9__* next; } ;
typedef  TYPE_1__ bitmap_element ;
typedef  TYPE_2__* bitmap ;
struct TYPE_10__ {unsigned int indx; TYPE_1__* current; TYPE_1__* first; } ;

/* Variables and functions */
 TYPE_1__* bitmap_element_allocate (TYPE_2__*) ; 
 int /*<<< orphan*/  gcc_assert (TYPE_1__*) ; 

__attribute__((used)) static bitmap_element *
bitmap_elt_insert_after (bitmap head, bitmap_element *elt, unsigned int indx)
{
  bitmap_element *node = bitmap_element_allocate (head);
  node->indx = indx;

  if (!elt)
    {
      if (!head->current)
	{
	  head->current = node;
	  head->indx = indx;
	}
      node->next = head->first;
      if (node->next)
	node->next->prev = node;
      head->first = node;
      node->prev = NULL;
    }
  else
    {
      gcc_assert (head->current);
      node->next = elt->next;
      if (node->next)
	node->next->prev = node;
      elt->next = node;
      node->prev = elt;
    }
  return node;
}