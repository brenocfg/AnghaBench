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
struct pred_data {int special; int* codes; int allows_non_const; int allows_non_lvalue; int singleton; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int CONCAT ; 
 scalar_t__ DEFINE_SPECIAL_PREDICATE ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_RTX_CLASS (int) ; 
 int MEM ; 
 char N ; 
 int NUM_RTX_CODE ; 
 int PARALLEL ; 
 int REG ; 
 scalar_t__ RTX_CONST_OBJ ; 
 int STRICT_LOW_PART ; 
 int SUBREG ; 
 int UNKNOWN ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XSTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_predicate (struct pred_data*) ; 
 int /*<<< orphan*/  compute_predicate_codes (int /*<<< orphan*/ ,char*) ; 
 struct pred_data* xcalloc (int,int) ; 

__attribute__((used)) static void
process_define_predicate (rtx desc)
{
  struct pred_data *pred = xcalloc (sizeof (struct pred_data), 1);
  char codes[NUM_RTX_CODE];
  bool seen_one = false;
  int i;

  pred->name = XSTR (desc, 0);
  if (GET_CODE (desc) == DEFINE_SPECIAL_PREDICATE)
    pred->special = 1;

  compute_predicate_codes (XEXP (desc, 1), codes);

  for (i = 0; i < NUM_RTX_CODE; i++)
    if (codes[i] != N)
      {
	pred->codes[i] = true;
	if (GET_RTX_CLASS (i) != RTX_CONST_OBJ)
	  pred->allows_non_const = true;
	if (i != REG
	    && i != SUBREG
	    && i != MEM
	    && i != CONCAT
	    && i != PARALLEL
	    && i != STRICT_LOW_PART)
	  pred->allows_non_lvalue = true;

	if (seen_one)
	  pred->singleton = UNKNOWN;
	else
	  {
	    pred->singleton = i;
	    seen_one = true;
	  }
      }
  add_predicate (pred);
}