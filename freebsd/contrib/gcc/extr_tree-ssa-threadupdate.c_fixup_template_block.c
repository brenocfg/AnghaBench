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
struct redirection_data {scalar_t__ dup_block; } ;
struct local_info {scalar_t__ template_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  create_edge_and_update_destination_phis (struct redirection_data*) ; 

__attribute__((used)) static int
fixup_template_block (void **slot, void *data)
{
  struct redirection_data *rd = (struct redirection_data *) *slot;
  struct local_info *local_info = (struct local_info *)data;

  /* If this is the template block, then create its outgoing edges
     and halt the hash table traversal.  */
  if (rd->dup_block && rd->dup_block == local_info->template_block)
    {
      create_edge_and_update_destination_phis (rd);
      return 0;
    }

  return 1;
}