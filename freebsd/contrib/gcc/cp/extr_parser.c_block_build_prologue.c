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
typedef  scalar_t__ tree ;
struct block_sema_info {int /*<<< orphan*/  block_body; scalar_t__ block_byref_decl_list; scalar_t__ block_ref_decl_list; } ;

/* Variables and functions */
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  declare_block_prologue_local_byref_vars (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  declare_block_prologue_local_vars (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 int /*<<< orphan*/  get_identifier (char*) ; 
 scalar_t__ lookup_name (int /*<<< orphan*/ ) ; 

void
block_build_prologue (struct block_sema_info *block_impl)
{
  tree chain;
  tree self_parm = lookup_name (get_identifier (".block_descriptor"));
  gcc_assert (self_parm);
  
  for (chain = block_impl->block_ref_decl_list; chain;
	chain = TREE_CHAIN (chain))
      declare_block_prologue_local_vars (self_parm, TREE_VALUE (chain),
					  block_impl->block_body);
  /* APPLE LOCAL begin radar 6169527 */
  for (chain = block_impl->block_byref_decl_list; chain;
	chain = TREE_CHAIN (chain))
      declare_block_prologue_local_byref_vars (self_parm, TREE_VALUE (chain),
						block_impl->block_body);
  /* APPLE LOCAL end radar 6169527 */
}