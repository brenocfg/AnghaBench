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
typedef  int /*<<< orphan*/ * tree ;
struct walk_stmt_info {int* info; } ;

/* Variables and functions */
#define  OMP_FOR 129 
#define  OMP_SECTIONS 128 
 int TREE_CODE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static tree
check_combined_parallel (tree *tp, int *walk_subtrees, void *data)
{
  struct walk_stmt_info *wi = data;
  int *info = wi->info;

  *walk_subtrees = 0;
  switch (TREE_CODE (*tp))
    {
    case OMP_FOR:
    case OMP_SECTIONS:
      *info = *info == 0 ? 1 : -1;
      break;
    default:
      *info = -1;
      break;
    }
  return NULL;
}