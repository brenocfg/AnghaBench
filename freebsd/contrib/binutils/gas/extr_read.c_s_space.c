#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int valueT ;
typedef  int /*<<< orphan*/  symbolS ;
typedef  int /*<<< orphan*/  relax_substateT ;
typedef  scalar_t__ offsetT ;
struct TYPE_7__ {scalar_t__ X_op; int X_add_number; int /*<<< orphan*/ * X_add_symbol; } ;
typedef  TYPE_1__ expressionS ;

/* Variables and functions */
 scalar_t__ O_constant ; 
 scalar_t__ O_symbol ; 
 int /*<<< orphan*/  SKIP_WHITESPACE () ; 
 long S_GET_VALUE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_SET_VALUE (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int abs_section_offset ; 
 scalar_t__ absolute_section ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  demand_empty_rest_of_line () ; 
 int /*<<< orphan*/  do_align (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_expr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  expression (TYPE_1__*) ; 
 scalar_t__ flag_m68k_mri ; 
 scalar_t__ flag_mri ; 
 int /*<<< orphan*/  frag_now ; 
 long frag_now_fix () ; 
 char* frag_var (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,char*) ; 
 char* input_line_pointer ; 
 int /*<<< orphan*/  know (int) ; 
 int /*<<< orphan*/ * line_label ; 
 int /*<<< orphan*/ * make_expr_symbol (TYPE_1__*) ; 
 int /*<<< orphan*/  md_flush_pending_output () ; 
 int /*<<< orphan*/  mri_comment_end (char*,char) ; 
 char* mri_comment_field (char*) ; 
 int /*<<< orphan*/ * mri_common_symbol ; 
 int mri_pending_align ; 
 int /*<<< orphan*/  need_pass_2 ; 
 scalar_t__ now_seg ; 
 int /*<<< orphan*/  resolve_expression (TYPE_1__*) ; 
 int /*<<< orphan*/  rs_fill ; 
 int /*<<< orphan*/  rs_space ; 
 int /*<<< orphan*/  subseg_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* symbol_get_value_expression (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbol_set_frag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  text_section ; 

void
s_space (int mult)
{
  expressionS exp;
  expressionS val;
  char *p = 0;
  char *stop = NULL;
  char stopc = 0;
  int bytes;

#ifdef md_flush_pending_output
  md_flush_pending_output ();
#endif

  if (flag_mri)
    stop = mri_comment_field (&stopc);

  /* In m68k MRI mode, we need to align to a word boundary, unless
     this is ds.b.  */
  if (flag_m68k_mri && mult > 1)
    {
      if (now_seg == absolute_section)
	{
	  abs_section_offset += abs_section_offset & 1;
	  if (line_label != NULL)
	    S_SET_VALUE (line_label, abs_section_offset);
	}
      else if (mri_common_symbol != NULL)
	{
	  valueT val;

	  val = S_GET_VALUE (mri_common_symbol);
	  if ((val & 1) != 0)
	    {
	      S_SET_VALUE (mri_common_symbol, val + 1);
	      if (line_label != NULL)
		{
		  expressionS *symexp;

		  symexp = symbol_get_value_expression (line_label);
		  know (symexp->X_op == O_symbol);
		  know (symexp->X_add_symbol == mri_common_symbol);
		  symexp->X_add_number += 1;
		}
	    }
	}
      else
	{
	  do_align (1, (char *) NULL, 0, 0);
	  if (line_label != NULL)
	    {
	      symbol_set_frag (line_label, frag_now);
	      S_SET_VALUE (line_label, frag_now_fix ());
	    }
	}
    }

  bytes = mult;

  expression (&exp);

  SKIP_WHITESPACE ();
  if (*input_line_pointer == ',')
    {
      ++input_line_pointer;
      expression (&val);
    }
  else
    {
      val.X_op = O_constant;
      val.X_add_number = 0;
    }

  if (val.X_op != O_constant
      || val.X_add_number < - 0x80
      || val.X_add_number > 0xff
      || (mult != 0 && mult != 1 && val.X_add_number != 0))
    {
      resolve_expression (&exp);
      if (exp.X_op != O_constant)
	as_bad (_("unsupported variable size or fill value"));
      else
	{
	  offsetT i;

	  if (mult == 0)
	    mult = 1;
	  bytes = mult * exp.X_add_number;
	  for (i = 0; i < exp.X_add_number; i++)
	    emit_expr (&val, mult);
	}
    }
  else
    {
      if (now_seg == absolute_section || mri_common_symbol != NULL)
	resolve_expression (&exp);

      if (exp.X_op == O_constant)
	{
	  long repeat;

	  repeat = exp.X_add_number;
	  if (mult)
	    repeat *= mult;
	  bytes = repeat;
	  if (repeat <= 0)
	    {
	      if (!flag_mri)
		as_warn (_(".space repeat count is zero, ignored"));
	      else if (repeat < 0)
		as_warn (_(".space repeat count is negative, ignored"));
	      goto getout;
	    }

	  /* If we are in the absolute section, just bump the offset.  */
	  if (now_seg == absolute_section)
	    {
	      abs_section_offset += repeat;
	      goto getout;
	    }

	  /* If we are secretly in an MRI common section, then
	     creating space just increases the size of the common
	     symbol.  */
	  if (mri_common_symbol != NULL)
	    {
	      S_SET_VALUE (mri_common_symbol,
			   S_GET_VALUE (mri_common_symbol) + repeat);
	      goto getout;
	    }

	  if (!need_pass_2)
	    p = frag_var (rs_fill, 1, 1, (relax_substateT) 0, (symbolS *) 0,
			  (offsetT) repeat, (char *) 0);
	}
      else
	{
	  if (now_seg == absolute_section)
	    {
	      as_bad (_("space allocation too complex in absolute section"));
	      subseg_set (text_section, 0);
	    }

	  if (mri_common_symbol != NULL)
	    {
	      as_bad (_("space allocation too complex in common section"));
	      mri_common_symbol = NULL;
	    }

	  if (!need_pass_2)
	    p = frag_var (rs_space, 1, 1, (relax_substateT) 0,
			  make_expr_symbol (&exp), (offsetT) 0, (char *) 0);
	}

      if (p)
	*p = val.X_add_number;
    }

 getout:

  /* In MRI mode, after an odd number of bytes, we must align to an
     even word boundary, unless the next instruction is a dc.b, ds.b
     or dcb.b.  */
  if (flag_mri && (bytes & 1) != 0)
    mri_pending_align = 1;

  demand_empty_rest_of_line ();

  if (flag_mri)
    mri_comment_end (stop, stopc);
}