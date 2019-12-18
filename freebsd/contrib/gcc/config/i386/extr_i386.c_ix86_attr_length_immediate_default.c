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
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_2__ {int n_operands; int /*<<< orphan*/ * operand; } ;

/* Variables and functions */
 scalar_t__ CONSTANT_P (int /*<<< orphan*/ ) ; 
#define  MODE_DI 131 
#define  MODE_HI 130 
#define  MODE_QI 129 
#define  MODE_SI 128 
 int /*<<< orphan*/  extract_insn_cached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal_insn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int get_attr_mode (int /*<<< orphan*/ ) ; 
 TYPE_1__ recog_data ; 
 scalar_t__ satisfies_constraint_K (int /*<<< orphan*/ ) ; 

int
ix86_attr_length_immediate_default (rtx insn, int shortform)
{
  int len = 0;
  int i;
  extract_insn_cached (insn);
  for (i = recog_data.n_operands - 1; i >= 0; --i)
    if (CONSTANT_P (recog_data.operand[i]))
      {
	gcc_assert (!len);
	if (shortform && satisfies_constraint_K (recog_data.operand[i]))
	  len = 1;
	else
	  {
	    switch (get_attr_mode (insn))
	      {
		case MODE_QI:
		  len+=1;
		  break;
		case MODE_HI:
		  len+=2;
		  break;
		case MODE_SI:
		  len+=4;
		  break;
		/* Immediates for DImode instructions are encoded as 32bit sign extended values.  */
		case MODE_DI:
		  len+=4;
		  break;
		default:
		  fatal_insn ("unknown insn mode", insn);
	      }
	  }
      }
  return len;
}