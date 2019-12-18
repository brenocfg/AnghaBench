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
typedef  int /*<<< orphan*/  tree ;
struct TYPE_2__ {int /*<<< orphan*/  num_ziv_unimplemented; int /*<<< orphan*/  num_ziv_independent; int /*<<< orphan*/  num_ziv_dependent; int /*<<< orphan*/  num_ziv; } ;

/* Variables and functions */
#define  INTEGER_CST 128 
 int /*<<< orphan*/  NULL_TREE ; 
 int TDF_DETAILS ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_dont_know ; 
 int /*<<< orphan*/  chrec_fold_minus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_known ; 
 TYPE_1__ dependence_stats ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 int /*<<< orphan*/  integer_type_node ; 
 int /*<<< orphan*/  integer_zero_node ; 
 int /*<<< orphan*/  integer_zerop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void 
analyze_ziv_subscript (tree chrec_a, 
		       tree chrec_b, 
		       tree *overlaps_a,
		       tree *overlaps_b, 
		       tree *last_conflicts)
{
  tree difference;
  dependence_stats.num_ziv++;
  
  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file, "(analyze_ziv_subscript \n");
  
  chrec_a = chrec_convert (integer_type_node, chrec_a, NULL_TREE);
  chrec_b = chrec_convert (integer_type_node, chrec_b, NULL_TREE);
  difference = chrec_fold_minus (integer_type_node, chrec_a, chrec_b);
  
  switch (TREE_CODE (difference))
    {
    case INTEGER_CST:
      if (integer_zerop (difference))
	{
	  /* The difference is equal to zero: the accessed index
	     overlaps for each iteration in the loop.  */
	  *overlaps_a = integer_zero_node;
	  *overlaps_b = integer_zero_node;
	  *last_conflicts = chrec_dont_know;
	  dependence_stats.num_ziv_dependent++;
	}
      else
	{
	  /* The accesses do not overlap.  */
	  *overlaps_a = chrec_known;
	  *overlaps_b = chrec_known;
	  *last_conflicts = integer_zero_node;
	  dependence_stats.num_ziv_independent++;
	}
      break;
      
    default:
      /* We're not sure whether the indexes overlap.  For the moment, 
	 conservatively answer "don't know".  */
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, "ziv test failed: difference is non-integer.\n");

      *overlaps_a = chrec_dont_know;
      *overlaps_b = chrec_dont_know;
      *last_conflicts = chrec_dont_know;
      dependence_stats.num_ziv_unimplemented++;
      break;
    }
  
  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file, ")\n");
}