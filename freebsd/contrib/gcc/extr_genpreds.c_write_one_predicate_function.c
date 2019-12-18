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
struct pred_data {char* name; int /*<<< orphan*/  exp; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_mode_tests (struct pred_data*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  write_predicate_stmts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_predicate_subfunction (struct pred_data*) ; 

__attribute__((used)) static void
write_one_predicate_function (struct pred_data *p)
{
  if (!p->exp)
    return;

  write_predicate_subfunction (p);
  add_mode_tests (p);

  /* A normal predicate can legitimately not look at enum machine_mode
     if it accepts only CONST_INTs and/or CONST_DOUBLEs.  */
  printf ("int\n%s (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)\n{\n",
	  p->name);
  write_predicate_stmts (p->exp);
  fputs ("}\n\n", stdout);
}