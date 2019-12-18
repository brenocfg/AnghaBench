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
struct rtx_iv {int mode; int extend_mode; int extend; int first_special; void* base; int /*<<< orphan*/  delta; int /*<<< orphan*/  mult; void* step; } ;
struct df_ref {int dummy; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/  CONSTANT_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINUS ; 
 void* NULL_RTX ; 
 int /*<<< orphan*/  PLUS ; 
 int /*<<< orphan*/  REG_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOIDmode ; 
 scalar_t__ analyzed_for_bivness_p (int /*<<< orphan*/ ,struct rtx_iv*) ; 
 int /*<<< orphan*/  const1_rtx ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  dump_iv_info (scalar_t__,struct rtx_iv*) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 int /*<<< orphan*/  get_biv_step (struct df_ref*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int*,int*,int /*<<< orphan*/ *) ; 
 int iv_constant (struct rtx_iv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  latch_dominating_def (int /*<<< orphan*/ ,struct df_ref**) ; 
 int /*<<< orphan*/  print_rtl (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  record_biv (int /*<<< orphan*/ ,struct rtx_iv*) ; 
 void* simplify_gen_binary (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
iv_analyze_biv (rtx def, struct rtx_iv *iv)
{
  rtx inner_step, outer_step;
  enum machine_mode inner_mode, outer_mode;
  enum rtx_code extend;
  struct df_ref *last_def;

  if (dump_file)
    {
      fprintf (dump_file, "Analyzing ");
      print_rtl (dump_file, def);
      fprintf (dump_file, " for bivness.\n");
    }
    
  if (!REG_P (def))
    {
      if (!CONSTANT_P (def))
	return false;

      return iv_constant (iv, def, VOIDmode);
    }

  if (!latch_dominating_def (def, &last_def))
    {
      if (dump_file)
	fprintf (dump_file, "  not simple.\n");
      return false;
    }

  if (!last_def)
    return iv_constant (iv, def, VOIDmode);

  if (analyzed_for_bivness_p (def, iv))
    {
      if (dump_file)
	fprintf (dump_file, "  already analysed.\n");
      return iv->base != NULL_RTX;
    }

  if (!get_biv_step (last_def, def, &inner_step, &inner_mode, &extend,
		     &outer_mode, &outer_step))
    {
      iv->base = NULL_RTX;
      goto end;
    }

  /* Loop transforms base to es (base + inner_step) + outer_step,
     where es means extend of subreg between inner_mode and outer_mode.
     The corresponding induction variable is

     es ((base - outer_step) + i * (inner_step + outer_step)) + outer_step  */

  iv->base = simplify_gen_binary (MINUS, outer_mode, def, outer_step);
  iv->step = simplify_gen_binary (PLUS, outer_mode, inner_step, outer_step);
  iv->mode = inner_mode;
  iv->extend_mode = outer_mode;
  iv->extend = extend;
  iv->mult = const1_rtx;
  iv->delta = outer_step;
  iv->first_special = inner_mode != outer_mode;

 end:
  if (dump_file)
    {
      fprintf (dump_file, "  ");
      dump_iv_info (dump_file, iv);
      fprintf (dump_file, "\n");
    }

  record_biv (def, iv);
  return iv->base != NULL_RTX;
}