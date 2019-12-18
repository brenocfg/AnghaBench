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
struct TYPE_2__ {unsigned int instruction; int relax_inst; int relax_size; } ;

/* Variables and functions */
 scalar_t__ FAIL ; 
 unsigned int LDST16_RI_MASK ; 
 int MAX_LITERAL_POOL_SIZE ; 
 int N16_LBUP ; 
 unsigned int N16_LHP ; 
 unsigned int N16_LIU ; 
 unsigned int N16_LWP ; 
 int N16_SBP ; 
 unsigned int N16_SHP ; 
 unsigned int N16_SWP ; 
 int /*<<< orphan*/  _IMM5 ; 
 int /*<<< orphan*/  _IMM5_RSHIFT_1 ; 
 int /*<<< orphan*/  _IMM5_RSHIFT_2 ; 
 int /*<<< orphan*/  _IMM8 ; 
 int end_of_line (char*) ; 
 int exp_ldst_offset (char**,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ inst ; 
 int reglow_required_here (char**,int) ; 
 int skip_past_comma (char**) ; 
 int /*<<< orphan*/  skip_whitespace (char*) ; 

__attribute__((used)) static void
do16_ldst_imm_insn (char *str)
{
  char data_exp[MAX_LITERAL_POOL_SIZE];
  int reg_rd;
  char *dataptr = NULL, *pp = NULL;
  int cnt = 0;
  int assign_data = (int) FAIL;
  unsigned int ldst_func;

  skip_whitespace (str);

  if (((reg_rd = reglow_required_here (&str, 8)) == (int) FAIL)
      || (skip_past_comma (&str) == (int) FAIL))
    return;

  skip_whitespace (str);
  dataptr = str;

  while ((*dataptr != '\0') && (*dataptr != '|') && (cnt <= MAX_LITERAL_POOL_SIZE))
    {
      data_exp[cnt] = *dataptr;
      dataptr++;
      cnt++;
    }

  data_exp[cnt] = '\0';
  pp = &data_exp[0];

  str = dataptr;

  ldst_func = inst.instruction & LDST16_RI_MASK;
  if (ldst_func == N16_LIU)
    assign_data = exp_ldst_offset (&pp, 0, _IMM8);
  else if (ldst_func == N16_LHP || ldst_func == N16_SHP)
    assign_data = exp_ldst_offset (&pp, 3, _IMM5_RSHIFT_1);
  else if (ldst_func == N16_LWP || ldst_func == N16_SWP)
    assign_data = exp_ldst_offset (&pp, 3, _IMM5_RSHIFT_2);
  else
    assign_data = exp_ldst_offset (&pp, 3, _IMM5);

  if ((assign_data == (int) FAIL) || (end_of_line (pp) == (int) FAIL))
    return;
  else
    {
      if ((inst.instruction & 0x7000) == N16_LIU)
        {
          inst.relax_inst |= ((inst.instruction >> 8) & 0xf) << 20
                          | ((inst.instruction & 0xff) << 1);
        }
      else if (((inst.instruction & 0x7007) == N16_LHP)
               || ((inst.instruction & 0x7007) == N16_SHP))
        {
          inst.relax_inst |= ((inst.instruction >> 8) & 0xf) << 20 | 2 << 15
                          | (((inst.instruction >> 3) & 0x1f) << 1);
        }
      else if (((inst.instruction & 0x7007) == N16_LWP)
               || ((inst.instruction & 0x7007) == N16_SWP))
        {
          inst.relax_inst |= ((inst.instruction >> 8) & 0xf) << 20 | 2 << 15
                          | (((inst.instruction >> 3) & 0x1f) << 2);
        }
      else if (((inst.instruction & 0x7007) == N16_LBUP)
               || ((inst.instruction & 0x7007) == N16_SBP))
        {
          inst.relax_inst |= ((inst.instruction >> 8) & 0xf) << 20 | 2 << 15
                          | (((inst.instruction >> 3) & 0x1f));
        }

      inst.relax_size = 4;
    }
}