#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct debug_write_fns {int /*<<< orphan*/  (* end_block ) (void*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* start_block ) (void*,int /*<<< orphan*/ ) ;} ;
struct debug_name {struct debug_name* next; } ;
struct debug_handle {int dummy; } ;
struct debug_block {int /*<<< orphan*/  end; int /*<<< orphan*/ * parent; TYPE_1__* locals; struct debug_block* next; struct debug_block* children; int /*<<< orphan*/  start; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_2__ {struct debug_name* list; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debug_write_linenos (struct debug_handle*,struct debug_write_fns const*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_write_name (struct debug_handle*,struct debug_write_fns const*,void*,struct debug_name*) ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
debug_write_block (struct debug_handle *info,
		   const struct debug_write_fns *fns, void *fhandle,
		   struct debug_block *block)
{
  struct debug_name *n;
  struct debug_block *b;

  if (! debug_write_linenos (info, fns, fhandle, block->start))
    return FALSE;

  /* I can't see any point to writing out a block with no local
     variables, so we don't bother, except for the top level block.  */
  if (block->locals != NULL || block->parent == NULL)
    {
      if (! (*fns->start_block) (fhandle, block->start))
	return FALSE;
    }

  if (block->locals != NULL)
    {
      for (n = block->locals->list; n != NULL; n = n->next)
	{
	  if (! debug_write_name (info, fns, fhandle, n))
	    return FALSE;
	}
    }

  for (b = block->children; b != NULL; b = b->next)
    {
      if (! debug_write_block (info, fns, fhandle, b))
	return FALSE;
    }

  if (! debug_write_linenos (info, fns, fhandle, block->end))
    return FALSE;

  if (block->locals != NULL || block->parent == NULL)
    {
      if (! (*fns->end_block) (fhandle, block->end))
	return FALSE;
    }

  return TRUE;
}