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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int BLKmode ; 
 int DECL_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_DECL_RTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VOIDmode ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  gen_reg_rtx (int) ; 
 int /*<<< orphan*/  gen_rtx_MEM (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
expand_one_error_var (tree var)
{
  enum machine_mode mode = DECL_MODE (var);
  rtx x;

  if (mode == BLKmode)
    x = gen_rtx_MEM (BLKmode, const0_rtx);
  else if (mode == VOIDmode)
    x = const0_rtx;
  else
    x = gen_reg_rtx (mode);

  SET_DECL_RTL (var, x);
}