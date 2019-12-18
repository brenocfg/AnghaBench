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
typedef  void* tree ;
struct mem_address {void* base; void* offset; void* index; void* step; } ;

/* Variables and functions */
 scalar_t__ INTEGER_CST ; 
 int /*<<< orphan*/  MULT_EXPR ; 
 void* NULL_TREE ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 scalar_t__ TREE_CODE (void*) ; 
 int /*<<< orphan*/  TREE_TYPE (void*) ; 
 int /*<<< orphan*/  copy_mem_ref_info (void*,void*) ; 
 void* create_mem_ref_raw (int /*<<< orphan*/ ,struct mem_address*) ; 
 void* fold_binary_to_constant (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*) ; 
 void* fold_convert (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  get_address_description (void*,struct mem_address*) ; 
 int /*<<< orphan*/  sizetype ; 

tree
maybe_fold_tmr (tree ref)
{
  struct mem_address addr;
  bool changed = false;
  tree ret, off;

  get_address_description (ref, &addr);

  if (addr.base && TREE_CODE (addr.base) == INTEGER_CST)
    {
      if (addr.offset)
	addr.offset = fold_binary_to_constant (PLUS_EXPR, sizetype,
			addr.offset,
			fold_convert (sizetype, addr.base));
      else
	addr.offset = addr.base;

      addr.base = NULL_TREE;
      changed = true;
    }

  if (addr.index && TREE_CODE (addr.index) == INTEGER_CST)
    {
      off = addr.index;
      if (addr.step)
	{
	  off = fold_binary_to_constant (MULT_EXPR, sizetype,
					 off, addr.step);
	  addr.step = NULL_TREE;
	}

      if (addr.offset)
	{
	  addr.offset = fold_binary_to_constant (PLUS_EXPR, sizetype,
						 addr.offset, off);
	}
      else
	addr.offset = off;

      addr.index = NULL_TREE;
      changed = true;
    }

  if (!changed)
    return NULL_TREE;
  
  ret = create_mem_ref_raw (TREE_TYPE (ref), &addr);
  if (!ret)
    return NULL_TREE;

  copy_mem_ref_info (ret, ref);
  return ret;
}