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
typedef  int /*<<< orphan*/  tree ;
struct tree_niter_desc {int /*<<< orphan*/  niter; int /*<<< orphan*/  may_be_zero; } ;
struct nfe_cache_elt {int /*<<< orphan*/  niter; int /*<<< orphan*/  exit; } ;
struct ivopts_data {int /*<<< orphan*/  current_loop; int /*<<< orphan*/  niters; } ;
typedef  int /*<<< orphan*/  edge ;
typedef  struct nfe_cache_elt* PTR ;

/* Variables and functions */
 int /*<<< orphan*/  INSERT ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  contains_abnormal_ssa_name_p (int /*<<< orphan*/ ) ; 
 struct nfe_cache_elt** htab_find_slot_with_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_hash_pointer (int /*<<< orphan*/ ) ; 
 scalar_t__ number_of_iterations_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tree_niter_desc*,int) ; 
 struct nfe_cache_elt* xmalloc (int) ; 
 scalar_t__ zero_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
niter_for_exit (struct ivopts_data *data, edge exit)
{
  struct nfe_cache_elt *nfe_desc;
  struct tree_niter_desc desc;
  PTR *slot;

  slot = htab_find_slot_with_hash (data->niters, exit,
				   htab_hash_pointer (exit),
				   INSERT);

  if (!*slot)
    {
      nfe_desc = xmalloc (sizeof (struct nfe_cache_elt));
      nfe_desc->exit = exit;

      /* Try to determine number of iterations.  We must know it
	 unconditionally (i.e., without possibility of # of iterations
	 being zero).  Also, we cannot safely work with ssa names that
	 appear in phi nodes on abnormal edges, so that we do not create
	 overlapping life ranges for them (PR 27283).  */
      if (number_of_iterations_exit (data->current_loop,
				     exit, &desc, true)
	  && zero_p (desc.may_be_zero)
     	  && !contains_abnormal_ssa_name_p (desc.niter))
	nfe_desc->niter = desc.niter;
      else
	nfe_desc->niter = NULL_TREE;
    }
  else
    nfe_desc = *slot;

  return nfe_desc->niter;
}