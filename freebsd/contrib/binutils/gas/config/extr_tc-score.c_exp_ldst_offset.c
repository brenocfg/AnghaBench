#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ X_op; int /*<<< orphan*/  X_add_number; } ;
struct TYPE_5__ {scalar_t__ pc_rel; TYPE_3__ exp; } ;
struct TYPE_8__ {int instruction; TYPE_1__ reloc; int /*<<< orphan*/  error; } ;
struct TYPE_6__ {int bits; int* range; } ;

/* Variables and functions */
 scalar_t__ FAIL ; 
 scalar_t__ O_constant ; 
 int SUCCESS ; 
 char* _ (char*) ; 
 unsigned int _IMM10_RSHIFT_2 ; 
 unsigned int _IMM14 ; 
 unsigned int _IMM15 ; 
 unsigned int _IMM16 ; 
 unsigned int _IMM4 ; 
 unsigned int _IMM5 ; 
 unsigned int _IMM5_RSHIFT_1 ; 
 unsigned int _IMM5_RSHIFT_2 ; 
 unsigned int _IMM8 ; 
 unsigned int _SIMM14_NEG ; 
 unsigned int _SIMM16_LA ; 
 unsigned int _VALUE_HI16 ; 
 unsigned int _VALUE_LO16 ; 
 int /*<<< orphan*/  err_msg ; 
 TYPE_4__ inst ; 
 int my_get_expression (TYPE_3__*,char**) ; 
 TYPE_2__* score_df_range ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int validate_immediate (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int validate_immediate_align (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int
exp_ldst_offset (char **str, int shift, unsigned int data_type)
{
  char *dataptr;

  dataptr = * str;

  if ((*dataptr == '0') && (*(dataptr + 1) == 'x')
      && (data_type != _SIMM16_LA)
      && (data_type != _VALUE_HI16)
      && (data_type != _VALUE_LO16)
      && (data_type != _IMM16)
      && (data_type != _IMM15)
      && (data_type != _IMM14)
      && (data_type != _IMM4)
      && (data_type != _IMM5)
      && (data_type != _IMM8)
      && (data_type != _IMM5_RSHIFT_1)
      && (data_type != _IMM5_RSHIFT_2)
      && (data_type != _SIMM14_NEG)
      && (data_type != _IMM10_RSHIFT_2))
    {
      data_type += 24;
    }

  if (my_get_expression (&inst.reloc.exp, str) == (int) FAIL)
    return (int) FAIL;

  if (inst.reloc.exp.X_op == O_constant)
    {
      /* Need to check the immediate align.  */
      int value = validate_immediate_align (inst.reloc.exp.X_add_number, data_type);

      if (value == (int) FAIL)
	return (int) FAIL;

      value = validate_immediate (inst.reloc.exp.X_add_number, data_type, 0);
      if (value == (int) FAIL)
        {
          if (data_type < 30)
            sprintf (err_msg,
                     _("invalid constant: %d bit expression not in range %d..%d"),
                     score_df_range[data_type].bits,
                     score_df_range[data_type].range[0], score_df_range[data_type].range[1]);
          else
            sprintf (err_msg,
                     _("invalid constant: %d bit expression not in range %d..%d"),
                     score_df_range[data_type - 24].bits,
                     score_df_range[data_type - 24].range[0], score_df_range[data_type - 24].range[1]);
          inst.error = err_msg;
          return (int) FAIL;
        }

      if (data_type == _IMM5_RSHIFT_1)
        {
          value >>= 1;
        }
      else if ((data_type == _IMM5_RSHIFT_2) || (data_type == _IMM10_RSHIFT_2))
        {
          value >>= 2;
        }

      if (score_df_range[data_type].range[0] != 0)
        {
          value &= (1 << score_df_range[data_type].bits) - 1;
        }

      inst.instruction |= value << shift;
    }
  else
    {
      inst.reloc.pc_rel = 0;
    }

  return SUCCESS;
}