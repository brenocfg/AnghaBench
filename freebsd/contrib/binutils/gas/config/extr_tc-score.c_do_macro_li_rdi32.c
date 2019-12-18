#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ X_add_symbol; } ;
struct TYPE_5__ {TYPE_1__ exp; } ;
struct TYPE_6__ {int bwarn; int /*<<< orphan*/  error; TYPE_2__ reloc; } ;

/* Variables and functions */
 scalar_t__ FAIL ; 
 int MAX_LITERAL_POOL_SIZE ; 
 int /*<<< orphan*/  REG_TYPE_SCORE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _SIMM16_LA ; 
 int /*<<< orphan*/  _VALUE_HI16 ; 
 int append_insn (char*,int /*<<< orphan*/ ) ; 
 int data_op2 (char**,int,int /*<<< orphan*/ ) ; 
 int end_of_line (char*) ; 
 TYPE_3__ inst ; 
 int reg_required_here (char**,int,int /*<<< orphan*/ ) ; 
 int skip_past_comma (char**) ; 
 int /*<<< orphan*/  skip_whitespace (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,char*) ; 

__attribute__((used)) static void
do_macro_li_rdi32 (char *str){

  int reg_rd;

  skip_whitespace (str);
  if ((reg_rd = reg_required_here (&str, 20, REG_TYPE_SCORE)) == (int) FAIL
      || skip_past_comma (&str) == (int) FAIL)
    {
      return;
    }
  else
    {
      char *keep_data = str;

      /* li rd, simm16.  */
      if (data_op2 (&str, 1, _SIMM16_LA) != (int) FAIL)
        {
          end_of_line (str);
          return;
        }
      /* li rd, imm32.  */
      else
        {
          char append_str[MAX_LITERAL_POOL_SIZE];

          str = keep_data;

          if ((data_op2 (&str, 1, _VALUE_HI16) == (int) FAIL)
              || (end_of_line (str) == (int) FAIL))
            {
              return;
            }
          else if (inst.reloc.exp.X_add_symbol)
            {
              inst.error = _("li rd label isn't correct instruction form");
              return;
            }
          else
            {
              sprintf (append_str, "ld_i32hi r%d, %s", reg_rd, keep_data);

              if (append_insn (append_str, TRUE) == (int) FAIL)
		return;
              else
                {
                  sprintf (append_str, "ld_i32lo r%d, %s", reg_rd, keep_data);
                  if (append_insn (append_str, TRUE) == (int) FAIL)
		    return;

                  /* Set bwarn as -1, so macro instruction itself will not be generated frag.  */
                  inst.bwarn = -1;
                }
            }
        }
    }
}