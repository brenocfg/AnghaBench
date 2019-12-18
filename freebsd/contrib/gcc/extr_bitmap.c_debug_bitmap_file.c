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
struct TYPE_4__ {int indx; unsigned int* bits; scalar_t__ prev; struct TYPE_4__* next; } ;
typedef  TYPE_1__ bitmap_element ;
typedef  TYPE_2__* bitmap ;
struct TYPE_5__ {int indx; TYPE_1__* first; scalar_t__ current; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned int BITMAP_ELEMENT_ALL_BITS ; 
 unsigned int BITMAP_ELEMENT_WORDS ; 
 unsigned int BITMAP_WORD_BITS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

void
debug_bitmap_file (FILE *file, bitmap head)
{
  bitmap_element *ptr;

  fprintf (file, "\nfirst = %p current = %p indx = %u\n",
	   (void *) head->first, (void *) head->current, head->indx);

  for (ptr = head->first; ptr; ptr = ptr->next)
    {
      unsigned int i, j, col = 26;

      fprintf (file, "\t%p next = %p prev = %p indx = %u\n\t\tbits = {",
	       (void*) ptr, (void*) ptr->next, (void*) ptr->prev, ptr->indx);

      for (i = 0; i < BITMAP_ELEMENT_WORDS; i++)
	for (j = 0; j < BITMAP_WORD_BITS; j++)
	  if ((ptr->bits[i] >> j) & 1)
	    {
	      if (col > 70)
		{
		  fprintf (file, "\n\t\t\t");
		  col = 24;
		}

	      fprintf (file, " %u", (ptr->indx * BITMAP_ELEMENT_ALL_BITS
				     + i * BITMAP_WORD_BITS + j));
	      col += 4;
	    }

      fprintf (file, " }\n");
    }
}