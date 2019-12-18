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
struct data_reference {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DR_REF (struct data_reference*) ; 
 int /*<<< orphan*/  DR_STEP (struct data_reference*) ; 
 int /*<<< orphan*/  REPORT_DETAILS ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_SIZE_UNIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ tree_int_cst_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vect_dump ; 
 scalar_t__ vect_print_dump_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
vect_analyze_data_ref_access (struct data_reference *dr)
{
  tree step = DR_STEP (dr);
  tree scalar_type = TREE_TYPE (DR_REF (dr));

  if (!step || tree_int_cst_compare (step, TYPE_SIZE_UNIT (scalar_type)))
    {
      if (vect_print_dump_info (REPORT_DETAILS))
	fprintf (vect_dump, "not consecutive access");
      return false;
    }
  return true;
}