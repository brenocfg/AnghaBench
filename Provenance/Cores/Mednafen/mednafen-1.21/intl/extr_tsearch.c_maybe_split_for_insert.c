#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* node ;
struct TYPE_5__ {int red; struct TYPE_5__* left; struct TYPE_5__* right; } ;

/* Variables and functions */

__attribute__((used)) static void
maybe_split_for_insert (node *rootp, node *parentp, node *gparentp,
                        int p_r, int gp_r, int mode)
{
  node root = *rootp;
  node *rp, *lp;
  rp = &(*rootp)->right;
  lp = &(*rootp)->left;

  /* See if we have to split this node (both successors red).  */
  if (mode == 1
      || ((*rp) != NULL && (*lp) != NULL && (*rp)->red && (*lp)->red))
    {
      /* This node becomes red, its successors black.  */
      root->red = 1;
      if (*rp)
        (*rp)->red = 0;
      if (*lp)
        (*lp)->red = 0;

      /* If the parent of this node is also red, we have to do
         rotations.  */
      if (parentp != NULL && (*parentp)->red)
        {
          node gp = *gparentp;
          node p = *parentp;
          /* There are two main cases:
             1. The edge types (left or right) of the two red edges differ.
             2. Both red edges are of the same type.
             There exist two symmetries of each case, so there is a total of
             4 cases.  */
          if ((p_r > 0) != (gp_r > 0))
            {
              /* Put the child at the top of the tree, with its parent
                 and grandparent as successors.  */
              p->red = 1;
              gp->red = 1;
              root->red = 0;
              if (p_r < 0)
                {
                  /* Child is left of parent.  */
                  p->left = *rp;
                  *rp = p;
                  gp->right = *lp;
                  *lp = gp;
                }
              else
                {
                  /* Child is right of parent.  */
                  p->right = *lp;
                  *lp = p;
                  gp->left = *rp;
                  *rp = gp;
                }
              *gparentp = root;
            }
          else
            {
              *gparentp = *parentp;
              /* Parent becomes the top of the tree, grandparent and
                 child are its successors.  */
              p->red = 0;
              gp->red = 1;
              if (p_r < 0)
                {
                  /* Left edges.  */
                  gp->left = p->right;
                  p->right = gp;
                }
              else
                {
                  /* Right edges.  */
                  gp->right = p->left;
                  p->left = gp;
                }
            }
        }
    }
}