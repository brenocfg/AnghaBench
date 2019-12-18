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
struct redirection_data {int /*<<< orphan*/ * dup_block; scalar_t__ do_not_duplicate; } ;
struct local_info {int /*<<< orphan*/ * template_block; int /*<<< orphan*/ * bb; } ;

/* Variables and functions */
 int /*<<< orphan*/  create_block_for_threading (int /*<<< orphan*/ *,struct redirection_data*) ; 
 int /*<<< orphan*/  create_edge_and_update_destination_phis (struct redirection_data*) ; 

__attribute__((used)) static int
create_duplicates (void **slot, void *data)
{
  struct redirection_data *rd = (struct redirection_data *) *slot;
  struct local_info *local_info = (struct local_info *)data;

  /* If this entry should not have a duplicate created, then there's
     nothing to do.  */
  if (rd->do_not_duplicate)
    return 1;

  /* Create a template block if we have not done so already.  Otherwise
     use the template to create a new block.  */
  if (local_info->template_block == NULL)
    {
      create_block_for_threading (local_info->bb, rd);
      local_info->template_block = rd->dup_block;

      /* We do not create any outgoing edges for the template.  We will
	 take care of that in a later traversal.  That way we do not
	 create edges that are going to just be deleted.  */
    }
  else
    {
      create_block_for_threading (local_info->template_block, rd);

      /* Go ahead and wire up outgoing edges and update PHIs for the duplicate
         block.  */
      create_edge_and_update_destination_phis (rd);
    }

  /* Keep walking the hash table.  */
  return 1;
}