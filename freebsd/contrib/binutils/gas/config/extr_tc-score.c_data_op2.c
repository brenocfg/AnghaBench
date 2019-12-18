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
typedef  enum score_data_type { ____Placeholder_score_data_type } score_data_type ;
struct TYPE_7__ {int X_add_number; int X_unsigned; scalar_t__ X_add_symbol; } ;
struct TYPE_5__ {TYPE_3__ exp; scalar_t__ pc_rel; int /*<<< orphan*/  type; } ;
struct TYPE_8__ {char* error; scalar_t__ type; int instruction; TYPE_1__ reloc; } ;
struct TYPE_6__ {int bits; int* range; } ;

/* Variables and functions */
 void* BAD_ARGS ; 
 int /*<<< orphan*/  BFD_RELOC_32 ; 
 int /*<<< orphan*/  BFD_RELOC_HI16_S ; 
 int /*<<< orphan*/  BFD_RELOC_LO16 ; 
 int /*<<< orphan*/  BFD_RELOC_SCORE_DUMMY_HI16 ; 
 int /*<<< orphan*/  BFD_RELOC_SCORE_GOT_LO16 ; 
 int /*<<< orphan*/  BFD_RELOC_SCORE_GPREL15 ; 
 scalar_t__ FAIL ; 
 scalar_t__ Insn_Type_SYN ; 
 scalar_t__ Insn_internal ; 
 int MAX_LITERAL_POOL_SIZE ; 
 scalar_t__ Rd_lvalueRs_SI15 ; 
 scalar_t__ Rd_rvalueRs_SI15 ; 
 int SUCCESS ; 
 char TOLOWER (char) ; 
 char* _ (char*) ; 
#define  _GP_IMM15 133 
 int _IMM10_RSHIFT_2 ; 
 int _IMM14 ; 
 int _IMM15 ; 
 int _IMM16 ; 
#define  _IMM16_LO16_pic 132 
 int _IMM16_NEG ; 
 int _IMM16_pic ; 
 int _IMM20 ; 
 int _IMM4 ; 
 int _IMM5 ; 
 int _IMM5_RANGE_8_31 ; 
 int _IMM5_RSHIFT_1 ; 
 int _IMM5_RSHIFT_2 ; 
 int _IMM8 ; 
 int _SIMM14 ; 
 int _SIMM14_NEG ; 
 int _SIMM16 ; 
#define  _SIMM16_LA 131 
 int _SIMM16_LA_POS ; 
 int _SIMM16_NEG ; 
#define  _SIMM16_pic 130 
#define  _VALUE_HI16 129 
#define  _VALUE_LO16 128 
 int /*<<< orphan*/  end_of_line (char*) ; 
 char* err_msg ; 
 TYPE_4__ inst ; 
 int my_get_expression (TYPE_3__*,char**) ; 
 TYPE_2__* score_df_range ; 
 int /*<<< orphan*/  skip_whitespace (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 int validate_immediate (int,int,int) ; 

__attribute__((used)) static int
data_op2 (char **str, int shift, enum score_data_type data_type)
{
  int value;
  char data_exp[MAX_LITERAL_POOL_SIZE];
  char *dataptr;
  int cnt = 0;
  char *pp = NULL;

  skip_whitespace (*str);
  inst.error = NULL;
  dataptr = * str;

  /* Set hex_p to zero.  */
  int hex_p = 0;

  while ((*dataptr != '\0') && (*dataptr != '|') && (cnt <= MAX_LITERAL_POOL_SIZE))     /* 0x7c = ='|' */
    {
      data_exp[cnt] = *dataptr;
      dataptr++;
      cnt++;
    }

  data_exp[cnt] = '\0';
  pp = (char *)&data_exp;

  if (*dataptr == '|')          /* process PCE */
    {
      if (my_get_expression (&inst.reloc.exp, &pp) == (int) FAIL)
        return (int) FAIL;
      end_of_line (pp);
      if (inst.error != 0)
        return (int) FAIL;       /* to ouptut_inst to printf out the error */
      *str = dataptr;
    }
  else                          /* process  16 bit */
    {
      if (my_get_expression (&inst.reloc.exp, str) == (int) FAIL)
        {
          return (int) FAIL;
        }

      dataptr = (char *)data_exp;
      for (; *dataptr != '\0'; dataptr++)
        {
          *dataptr = TOLOWER (*dataptr);
          if (*dataptr == '!' || *dataptr == ' ')
            break;
        }
      dataptr = (char *)data_exp;

      if ((dataptr != NULL)
          && (((strstr (dataptr, "0x")) != NULL)
              || ((strstr (dataptr, "0X")) != NULL)))
        {
          hex_p = 1;
          if ((data_type != _SIMM16_LA)
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
              && (data_type != _SIMM14)
              && (data_type != _SIMM14_NEG)
              && (data_type != _SIMM16_NEG)
              && (data_type != _IMM10_RSHIFT_2)
              && (data_type != _GP_IMM15))
            {
              data_type += 24;
            }
        }

      if ((inst.reloc.exp.X_add_number == 0)
          && (inst.type != Insn_Type_SYN)
          && (inst.type != Rd_rvalueRs_SI15)
          && (inst.type != Rd_lvalueRs_SI15)
          && (inst.type != Insn_internal)
          && (((*dataptr >= 'a') && (*dataptr <= 'z'))
             || ((*dataptr == '0') && (*(dataptr + 1) == 'x') && (*(dataptr + 2) != '0'))
             || ((*dataptr == '+') && (*(dataptr + 1) != '0'))
             || ((*dataptr == '-') && (*(dataptr + 1) != '0'))))
        {
          inst.error = BAD_ARGS;
          return (int) FAIL;
        }
    }

  if ((inst.reloc.exp.X_add_symbol)
      && ((data_type == _SIMM16)
          || (data_type == _SIMM16_NEG)
          || (data_type == _IMM16_NEG)
          || (data_type == _SIMM14)
          || (data_type == _SIMM14_NEG)
          || (data_type == _IMM5)
          || (data_type == _IMM14)
          || (data_type == _IMM20)
          || (data_type == _IMM16)
          || (data_type == _IMM15)
          || (data_type == _IMM4)))
    {
      inst.error = BAD_ARGS;
      return (int) FAIL;
    }

  if (inst.reloc.exp.X_add_symbol)
    {
      switch (data_type)
        {
        case _SIMM16_LA:
          return (int) FAIL;
        case _VALUE_HI16:
          inst.reloc.type = BFD_RELOC_HI16_S;
          inst.reloc.pc_rel = 0;
          break;
        case _VALUE_LO16:
          inst.reloc.type = BFD_RELOC_LO16;
          inst.reloc.pc_rel = 0;
          break;
        case _GP_IMM15:
          inst.reloc.type = BFD_RELOC_SCORE_GPREL15;
          inst.reloc.pc_rel = 0;
          break;
        case _SIMM16_pic:
        case _IMM16_LO16_pic:
          inst.reloc.type = BFD_RELOC_SCORE_GOT_LO16;
          inst.reloc.pc_rel = 0;
          break;
        default:
          inst.reloc.type = BFD_RELOC_32;
          inst.reloc.pc_rel = 0;
          break;
        }
    }
  else
    {
      if (data_type == _IMM16_pic)
	{
          inst.reloc.type = BFD_RELOC_SCORE_DUMMY_HI16;
          inst.reloc.pc_rel = 0;
	}

      if (data_type == _SIMM16_LA && inst.reloc.exp.X_unsigned == 1)
        {
          value = validate_immediate (inst.reloc.exp.X_add_number, _SIMM16_LA_POS, hex_p);
          if (value == (int) FAIL)       /* for advance to check if this is ldis */
            if ((inst.reloc.exp.X_add_number & 0xffff) == 0)
              {
                inst.instruction |= 0x8000000;
                inst.instruction |= ((inst.reloc.exp.X_add_number >> 16) << 1) & 0x1fffe;
                return SUCCESS;
              }
        }
      else
        {
          value = validate_immediate (inst.reloc.exp.X_add_number, data_type, hex_p);
        }

      if (value == (int) FAIL)
        {
          if ((data_type != _SIMM14_NEG) && (data_type != _SIMM16_NEG) && (data_type != _IMM16_NEG))
            {
              sprintf (err_msg,
                       _("invalid constant: %d bit expression not in range %d..%d"),
                       score_df_range[data_type].bits,
                       score_df_range[data_type].range[0], score_df_range[data_type].range[1]);
            }
          else
            {
              sprintf (err_msg,
                       _("invalid constant: %d bit expression not in range %d..%d"),
                       score_df_range[data_type].bits,
                       -score_df_range[data_type].range[1], -score_df_range[data_type].range[0]);
            }

          inst.error = err_msg;
          return (int) FAIL;
        }

      if ((score_df_range[data_type].range[0] != 0) || (data_type == _IMM5_RANGE_8_31))
        {
          value &= (1 << score_df_range[data_type].bits) - 1;
        }

      inst.instruction |= value << shift;
    }

  if ((inst.instruction & 0xf0000000) == 0x30000000)
    {
      if ((((inst.instruction >> 20) & 0x1F) != 0)
          && (((inst.instruction >> 20) & 0x1F) != 1)
          && (((inst.instruction >> 20) & 0x1F) != 2)
          && (((inst.instruction >> 20) & 0x1F) != 3)
          && (((inst.instruction >> 20) & 0x1F) != 4)
          && (((inst.instruction >> 20) & 0x1F) != 8)
          && (((inst.instruction >> 20) & 0x1F) != 9)
          && (((inst.instruction >> 20) & 0x1F) != 0xa)
          && (((inst.instruction >> 20) & 0x1F) != 0xb)
          && (((inst.instruction >> 20) & 0x1F) != 0xc)
          && (((inst.instruction >> 20) & 0x1F) != 0xd)
          && (((inst.instruction >> 20) & 0x1F) != 0xe)
          && (((inst.instruction >> 20) & 0x1F) != 0x10)
          && (((inst.instruction >> 20) & 0x1F) != 0x11)
          && (((inst.instruction >> 20) & 0x1F) != 0x18)
          && (((inst.instruction >> 20) & 0x1F) != 0x1A)
          && (((inst.instruction >> 20) & 0x1F) != 0x1B)
          && (((inst.instruction >> 20) & 0x1F) != 0x1d)
          && (((inst.instruction >> 20) & 0x1F) != 0x1e)
          && (((inst.instruction >> 20) & 0x1F) != 0x1f))
        {
          inst.error = _("invalid constant: bit expression not defined");
          return (int) FAIL;
        }
    }

  return SUCCESS;
}