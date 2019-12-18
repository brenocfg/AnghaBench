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
struct nrv_data {scalar_t__ var; scalar_t__ result; } ;

/* Variables and functions */
 scalar_t__ NULL_TREE ; 
 scalar_t__ TYPE_P (scalar_t__) ; 

__attribute__((used)) static tree
finalize_nrv_r (tree *tp, int *walk_subtrees, void *data)
{
  struct nrv_data *dp = (struct nrv_data *)data;

  /* No need to walk into types.  */
  if (TYPE_P (*tp))
    *walk_subtrees = 0;

  /* Otherwise replace all occurrences of VAR with RESULT.  */
  else if (*tp == dp->var)
    *tp = dp->result;

  /* Keep iterating.  */
  return NULL_TREE;
}