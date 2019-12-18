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

/* Variables and functions */
 scalar_t__ FAIL ; 
 int /*<<< orphan*/  REG_TYPE_SCORE ; 
 int /*<<< orphan*/  _VALUE_LO16 ; 
 int /*<<< orphan*/  data_op2 (char**,int,int /*<<< orphan*/ ) ; 
 int reg_required_here (char**,int,int /*<<< orphan*/ ) ; 
 int skip_past_comma (char**) ; 
 int /*<<< orphan*/  skip_whitespace (char*) ; 

__attribute__((used)) static void
do_macro_rdi32lo (char *str)
{
  skip_whitespace (str);

  /* Do not handle end_of_line().  */
  if (reg_required_here (&str, 20, REG_TYPE_SCORE) != (int) FAIL
      && skip_past_comma (&str) != (int) FAIL)
    data_op2 (&str, 1, _VALUE_LO16);
}