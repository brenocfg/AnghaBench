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
struct rtx_iv {int dummy; } ;
struct df_ref {int dummy; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum iv_grd_result { ____Placeholder_iv_grd_result } iv_grd_result ;

/* Variables and functions */
 scalar_t__ CONSTANT_P (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int GRD_INVALID ; 
 int GRD_INVARIANT ; 
 int GRD_MAYBE_BIV ; 
 scalar_t__ SUBREG ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOIDmode ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  dump_iv_info (scalar_t__,struct rtx_iv*) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 int iv_analyze_biv (int /*<<< orphan*/ ,struct rtx_iv*) ; 
 int iv_analyze_def (struct df_ref*,struct rtx_iv*) ; 
 int /*<<< orphan*/  iv_constant (struct rtx_iv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iv_get_reaching_def (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct df_ref**) ; 
 int iv_subreg (struct rtx_iv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_rtl (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_rtl_single (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subreg_lowpart_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
iv_analyze_op (rtx insn, rtx op, struct rtx_iv *iv)
{
  struct df_ref *def = NULL;
  enum iv_grd_result res;

  if (dump_file)
    {
      fprintf (dump_file, "Analysing operand ");
      print_rtl (dump_file, op);
      fprintf (dump_file, " of insn ");
      print_rtl_single (dump_file, insn);
    }

  if (CONSTANT_P (op))
    res = GRD_INVARIANT;
  else if (GET_CODE (op) == SUBREG)
    {
      if (!subreg_lowpart_p (op))
	return false;

      if (!iv_analyze_op (insn, SUBREG_REG (op), iv))
	return false;

      return iv_subreg (iv, GET_MODE (op));
    }
  else
    {
      res = iv_get_reaching_def (insn, op, &def);
      if (res == GRD_INVALID)
	{
	  if (dump_file)
	    fprintf (dump_file, "  not simple.\n");
	  return false;
	}
    }

  if (res == GRD_INVARIANT)
    {
      iv_constant (iv, op, VOIDmode);

      if (dump_file)
	{
	  fprintf (dump_file, "  ");
	  dump_iv_info (dump_file, iv);
	  fprintf (dump_file, "\n");
	}
      return true;
    }

  if (res == GRD_MAYBE_BIV)
    return iv_analyze_biv (op, iv);

  return iv_analyze_def (def, iv);
}