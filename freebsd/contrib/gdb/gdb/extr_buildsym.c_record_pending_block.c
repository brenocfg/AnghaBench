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
struct pending_block {struct pending_block* next; struct block* block; } ;
struct objfile {int /*<<< orphan*/  objfile_obstack; } ;
struct block {int dummy; } ;

/* Variables and functions */
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,int) ; 
 struct pending_block* pending_blocks ; 

void
record_pending_block (struct objfile *objfile, struct block *block,
		      struct pending_block *opblock)
{
  struct pending_block *pblock;

  pblock = (struct pending_block *)
    obstack_alloc (&objfile->objfile_obstack, sizeof (struct pending_block));
  pblock->block = block;
  if (opblock)
    {
      pblock->next = opblock->next;
      opblock->next = pblock;
    }
  else
    {
      pblock->next = pending_blocks;
      pending_blocks = pblock;
    }
}