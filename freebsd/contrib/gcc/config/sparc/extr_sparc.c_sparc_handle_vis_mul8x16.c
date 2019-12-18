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

/* Variables and functions */
#define  CODE_FOR_fmul8x16_vis 130 
#define  CODE_FOR_fmul8x16al_vis 129 
#define  CODE_FOR_fmul8x16au_vis 128 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int TREE_INT_CST_LOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  nreverse (int /*<<< orphan*/ ) ; 
 int sparc_vis_mul8x16 (int,int) ; 
 int /*<<< orphan*/  tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
sparc_handle_vis_mul8x16 (int fncode, tree inner_type, tree elts0, tree elts1)
{
  tree n_elts = NULL_TREE;
  int scale;

  switch (fncode)
    {
    case CODE_FOR_fmul8x16_vis:
      for (; elts0 && elts1;
	   elts0 = TREE_CHAIN (elts0), elts1 = TREE_CHAIN (elts1))
	{
	  int val
	    = sparc_vis_mul8x16 (TREE_INT_CST_LOW (TREE_VALUE (elts0)),
				 TREE_INT_CST_LOW (TREE_VALUE (elts1)));
	  n_elts = tree_cons (NULL_TREE,
			      build_int_cst (inner_type, val),
			      n_elts);
	}
      break;

    case CODE_FOR_fmul8x16au_vis:
      scale = TREE_INT_CST_LOW (TREE_VALUE (elts1));

      for (; elts0; elts0 = TREE_CHAIN (elts0))
	{
	  int val
	    = sparc_vis_mul8x16 (TREE_INT_CST_LOW (TREE_VALUE (elts0)),
				 scale);
	  n_elts = tree_cons (NULL_TREE,
			      build_int_cst (inner_type, val),
			      n_elts);
	}
      break;

    case CODE_FOR_fmul8x16al_vis:
      scale = TREE_INT_CST_LOW (TREE_VALUE (TREE_CHAIN (elts1)));

      for (; elts0; elts0 = TREE_CHAIN (elts0))
	{
	  int val
	    = sparc_vis_mul8x16 (TREE_INT_CST_LOW (TREE_VALUE (elts0)),
				 scale);
	  n_elts = tree_cons (NULL_TREE,
			      build_int_cst (inner_type, val),
			      n_elts);
	}
      break;

    default:
      gcc_unreachable ();
    }

  return nreverse (n_elts);

}