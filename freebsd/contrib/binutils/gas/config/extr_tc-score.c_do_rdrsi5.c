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
struct TYPE_2__ {int instruction; int relax_inst; int relax_size; } ;

/* Variables and functions */
 scalar_t__ FAIL ; 
 int /*<<< orphan*/  REG_TYPE_SCORE ; 
 int /*<<< orphan*/  _IMM5 ; 
 int data_op2 (char**,int,int /*<<< orphan*/ ) ; 
 int end_of_line (char*) ; 
 TYPE_1__ inst ; 
 int reg_required_here (char**,int,int /*<<< orphan*/ ) ; 
 int skip_past_comma (char**) ; 
 int /*<<< orphan*/  skip_whitespace (char*) ; 

__attribute__((used)) static void
do_rdrsi5 (char *str)           /* 0~((2^14)-1) */
{
  skip_whitespace (str);

  if (reg_required_here (&str, 20, REG_TYPE_SCORE) == (int) FAIL
      || skip_past_comma (&str) == (int) FAIL
      || reg_required_here (&str, 15, REG_TYPE_SCORE) == (int) FAIL
      || skip_past_comma (&str) == (int) FAIL
      || data_op2 (&str, 10, _IMM5) == (int) FAIL
      || end_of_line (str) == (int) FAIL)
    return;

  if ((((inst.instruction >> 20) & 0x1f) == ((inst.instruction >> 15) & 0x1f))
      && (inst.relax_inst != 0x8000) && (((inst.instruction >> 15) & 0x10) == 0))
    {
      inst.relax_inst |= (((inst.instruction >> 10) & 0x1f) << 3) | (((inst.instruction >> 15) & 0xf) << 8);
      inst.relax_size = 2;
    }
  else
    inst.relax_inst = 0x8000;
}