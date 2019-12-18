#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pending_block {struct pending_block* next; } ;

/* Variables and functions */
 struct pending_block* pending_blocks ; 
 int /*<<< orphan*/  xfree (void*) ; 

void
free_pending_blocks (void)
{
#if 0				/* Now we make the links in the
				   objfile_obstack, so don't free
				   them.  */
  struct pending_block *bnext, *bnext1;

  for (bnext = pending_blocks; bnext; bnext = bnext1)
    {
      bnext1 = bnext->next;
      xfree ((void *) bnext);
    }
#endif
  pending_blocks = NULL;
}