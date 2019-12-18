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
typedef  int /*<<< orphan*/  TREE_TYPE ;

/* Variables and functions */
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  SCEV_KNOWN ; 
 int /*<<< orphan*/  SCEV_NOT_KNOWN ; 
 scalar_t__ chrec_dont_know ; 
 int /*<<< orphan*/  chrec_known ; 
 scalar_t__ chrec_not_analyzed_yet ; 
 void* make_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static void
initialize_scalar_evolutions_analyzer (void)
{
  /* The elements below are unique.  */
  if (chrec_dont_know == NULL_TREE)
    {
      chrec_not_analyzed_yet = NULL_TREE;
      chrec_dont_know = make_node (SCEV_NOT_KNOWN);
      chrec_known = make_node (SCEV_KNOWN);
      TREE_TYPE (chrec_dont_know) = void_type_node;
      TREE_TYPE (chrec_known) = void_type_node;
    }
}