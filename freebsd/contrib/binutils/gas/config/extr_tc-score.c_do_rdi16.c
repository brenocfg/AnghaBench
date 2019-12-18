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
 int /*<<< orphan*/  _IMM16 ; 
 int data_op2 (char**,int,int /*<<< orphan*/ ) ; 
 int end_of_line (char*) ; 
 int reg_required_here (char**,int,int /*<<< orphan*/ ) ; 
 int skip_past_comma (char**) ; 
 int /*<<< orphan*/  skip_whitespace (char*) ; 

__attribute__((used)) static void
do_rdi16 (char *str)
{
  skip_whitespace (str);

  if (reg_required_here (&str, 20, REG_TYPE_SCORE) == (int) FAIL
      || skip_past_comma (&str) == (int) FAIL
      || data_op2 (&str, 1, _IMM16) == (int) FAIL
      || end_of_line (str) == (int) FAIL)
    return;
  /*
  if (((inst.instruction & 0xa0dfffe) != 0xa0c0000) || ((((inst.instruction >> 20) & 0x1f) & 0x10) == 0x10))
    inst.relax_inst = 0x8000;
  else
    inst.relax_size = 2;
  */
}